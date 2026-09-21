#include "../includes/cub3d.h"

static void	init_ray(t_game *g, int x)
{
	t_raycast	*r;

	r = &g->raycast;
	r->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.pos_x;
	r->map_y = (int)g->player.pos_y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
	r->hit = 0;
}

static void	init_step(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.pos_y) * r->delta_dist_y;
	}
}

/* DDA: avanza por la rejilla hasta chocar con '1'. Con guarda de bordes. */
static void	perform_dda(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_x >= g->map.width || r->map_y >= g->map.height)
		{
			r->hit = 1;
			r->perp_wall_dist = 1e30;
			return ;
		}
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	if (r->perp_wall_dist < 0.0001)
		r->perp_wall_dist = 0.0001;
}

void	cast_ray(t_game *g, int x)
{
	init_ray(g, x);
	init_step(g);
	perform_dda(g);
	compute_wall_bounds(g);
	compute_tex_x(g);
}

void	compute_wall_bounds(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	r->line_height = (int)(WIN_H / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_H / 2;
	r->draw_end = r->line_height / 2 + WIN_H / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= WIN_H)
		r->draw_end = WIN_H - 1;
}

/* wall_x = punto exacto de impacto en [0,1); tex_x con corrección espejo. */
void	compute_tex_x(t_game *g)
{
	t_raycast	*r;
	t_img		*tex;

	r = &g->raycast;
	if (r->side == 0)
		r->wall_x = g->player.pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = g->player.pos_x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	tex = select_texture(g, r);
	r->tex_x = (int)(r->wall_x * (double)tex->width);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = tex->width - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = tex->width - r->tex_x - 1;
}
