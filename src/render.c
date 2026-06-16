#include "../include/cub3d.h"

static intpick_tex_id(int side, double ray_dir_x, double ray_dir_y)
{
if (side == 0)
{
if (ray_dir_x > 0)
return (TEX_WE);
return (TEX_EA);
}
if (ray_dir_y > 0)
return (TEX_NO);
return (TEX_SO);
}

static voiddraw_column(t_game *g, int x, int draw_start, int draw_end, int color)
{
inty;

y = draw_start;
while (y <= draw_end)
{
g->frame.data[y * WIN_W + x] = color;
y++;
}
}

static voidraycast_column(t_game *g, int x)
{
doublecamera_x;
doubleray_dir_x;
doubleray_dir_y;
intmap_x;
intmap_y;
doubledelta_x;
doubledelta_y;
doubleside_x;
doubleside_y;
intstep_x;
intstep_y;
intside;
doubleperp_dist;
intline_h;
intdraw_start;
intdraw_end;
doublewall_x;
inttex_x;
t_img*tex;
inttex_y;
doublestep;
doubletex_pos;
inty;

camera_x = 2.0 * x / (double)WIN_W - 1.0;
ray_dir_x = g->player.dir_x + g->player.plane_x * camera_x;
ray_dir_y = g->player.dir_y + g->player.plane_y * camera_x;
map_x = (int)g->player.x;
map_y = (int)g->player.y;
delta_x = fabs(1.0 / (ray_dir_x == 0 ? 1e-30 : ray_dir_x));
delta_y = fabs(1.0 / (ray_dir_y == 0 ? 1e-30 : ray_dir_y));
if (ray_dir_x < 0)
{
step_x = -1;
side_x = (g->player.x - map_x) * delta_x;
}
else
{
step_x = 1;
side_x = (map_x + 1.0 - g->player.x) * delta_x;
}
if (ray_dir_y < 0)
{
step_y = -1;
side_y = (g->player.y - map_y) * delta_y;
}
else
{
step_y = 1;
side_y = (map_y + 1.0 - g->player.y) * delta_y;
}
while (1)
{
if (side_x < side_y)
{
side_x += delta_x;
map_x += step_x;
side = 0;
}
else
{
side_y += delta_y;
map_y += step_y;
side = 1;
}
if (map_x < 0 || map_y < 0 || map_x >= g->cfg.map_w || map_y >= g->cfg.map_h)
return ;
if (g->cfg.map[map_y][map_x] == '1')
break ;
}
if (side == 0)
perp_dist = (map_x - g->player.x + (1 - step_x) / 2.0) / ray_dir_x;
else
perp_dist = (map_y - g->player.y + (1 - step_y) / 2.0) / ray_dir_y;
if (perp_dist <= 0)
perp_dist = 0.01;
line_h = (int)(WIN_H / perp_dist);
draw_start = -line_h / 2 + WIN_H / 2;
if (draw_start < 0)
draw_start = 0;
draw_end = line_h / 2 + WIN_H / 2;
if (draw_end >= WIN_H)
draw_end = WIN_H - 1;
if (side == 0)
wall_x = g->player.y + perp_dist * ray_dir_y;
else
wall_x = g->player.x + perp_dist * ray_dir_x;
wall_x -= floor(wall_x);
tex = &g->textures[pick_tex_id(side, ray_dir_x, ray_dir_y)];
tex_x = (int)(wall_x * (double)tex->width);
if (side == 0 && ray_dir_x > 0)
tex_x = tex->width - tex_x - 1;
if (side == 1 && ray_dir_y < 0)
tex_x = tex->width - tex_x - 1;
step = 1.0 * tex->height / line_h;
tex_pos = (draw_start - WIN_H / 2 + line_h / 2) * step;
y = draw_start;
while (y <= draw_end)
{
tex_y = (int)tex_pos & (tex->height - 1);
tex_pos += step;
g->frame.data[y * WIN_W + x] = tex->data[tex_y * tex->width + tex_x];
y++;
}
}

voidrender_frame(t_game *g)
{
intx;

x = 0;
while (x < WIN_W)
{
draw_column(g, x, 0, WIN_H / 2 - 1, g->cfg.ceil_color);
draw_column(g, x, WIN_H / 2, WIN_H - 1, g->cfg.floor_color);
raycast_column(g, x);
x++;
}
mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
}

voidload_textures(t_game *game)
{
inti;

i = 0;
while (i < 4)
{
game->textures[i].ptr = mlx_xpm_file_to_image(game->mlx, game->cfg.tex_path[i],
&game->textures[i].width, &game->textures[i].height);
if (!game->textures[i].ptr)
exit_error(game, "Failed to load texture");
game->textures[i].data = (int *)mlx_get_data_addr(game->textures[i].ptr,
&game->textures[i].bpp, &game->textures[i].size_line,
&game->textures[i].endian);
i++;
}
}
