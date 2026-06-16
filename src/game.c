#include "../include/cub3d.h"

static intcan_walk(t_game *game, double x, double y)
{
intix;
intiy;
charcell;

ix = (int)x;
iy = (int)y;
if (ix < 0 || iy < 0 || ix >= game->cfg.map_w || iy >= game->cfg.map_h)
return (0);
cell = game->cfg.map[iy][ix];
return (cell != '1' && cell != ' ');
}

static voidrotate_player(t_player *p, double angle)
{
doubleold_dir_x;
doubleold_plane_x;

old_dir_x = p->dir_x;
p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
old_plane_x = p->plane_x;
p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

static voidupdate_player(t_game *game)
{
doublenx;
doubleny;
doublestrafe_x;
doublestrafe_y;

nx = game->player.x;
ny = game->player.y;
if (game->input.w)
{
nx += game->player.dir_x * game->player.move_speed;
ny += game->player.dir_y * game->player.move_speed;
}
if (game->input.s)
{
nx -= game->player.dir_x * game->player.move_speed;
ny -= game->player.dir_y * game->player.move_speed;
}
strafe_x = game->player.plane_x * game->player.move_speed;
strafe_y = game->player.plane_y * game->player.move_speed;
if (game->input.a)
{
nx -= strafe_x;
ny -= strafe_y;
}
if (game->input.d)
{
nx += strafe_x;
ny += strafe_y;
}
if (can_walk(game, nx, game->player.y))
game->player.x = nx;
if (can_walk(game, game->player.x, ny))
game->player.y = ny;
if (game->input.left)
rotate_player(&game->player, -game->player.rot_speed);
if (game->input.right)
rotate_player(&game->player, game->player.rot_speed);
}

voidinit_game(t_game *game)
{
game->mlx = mlx_init();
if (!game->mlx)
exit_error(game, "mlx_init failed");
game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
if (!game->win)
exit_error(game, "mlx_new_window failed");
game->frame.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
if (!game->frame.ptr)
exit_error(game, "mlx_new_image failed");
game->frame.data = (int *)mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
&game->frame.size_line, &game->frame.endian);
game->frame.width = WIN_W;
game->frame.height = WIN_H;
}

inton_close(t_game *game)
{
inti;

i = 0;
while (i < 4)
{
if (game->textures[i].ptr)
mlx_destroy_image(game->mlx, game->textures[i].ptr);
i++;
}
if (game->frame.ptr)
mlx_destroy_image(game->mlx, game->frame.ptr);
if (game->win)
mlx_destroy_window(game->mlx, game->win);
if (game->mlx)
{
mlx_destroy_display(game->mlx);
free(game->mlx);
}
free_config(&game->cfg);
exit(0);
}

intrender_loop(t_game *game)
{
update_player(game);
render_frame(game);
return (0);
}
