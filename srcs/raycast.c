/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:15:47 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/09/22 14:15:48 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Calcula la dirección del rayo para la columna x y las distancias
 * delta según el plano de cámara del jugador.
 * Retorna: nada.
 *
 * Computes the ray direction for column x and the delta distances
 * from the player's camera plane.
 * Returns: nothing.
 */
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

/*
 * Calcula el paso (step) y la distancia lateral inicial en cada eje
 * según el signo de la dirección del rayo.
 * Retorna: nada.
 *
 * Computes the step and the initial side distance on each axis based
 * on the ray direction's sign.
 * Returns: nothing.
 */
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

/*
 * Avanza por la rejilla del mapa (DDA) hasta chocar con una pared
 * ('1') o salirse de los límites del mapa.
 * Retorna: nada.
 *
 * Steps through the map grid (DDA) until it hits a wall ('1') or
 * goes outside the map bounds.
 * Returns: nothing.
 */
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

/*
 * Lanza el rayo completo de la columna x: dirección, DDA, altura de
 * pared en pantalla y coordenada de textura.
 * Retorna: nada.
 *
 * Casts the full ray for column x: direction, DDA, on-screen wall
 * height and texture coordinate.
 * Returns: nothing.
 */
void	cast_ray(t_game *g, int x)
{
	init_ray(g, x);
	init_step(g);
	perform_dda(g);
	compute_wall_bounds(g);
	compute_tex_x(g);
}

/*
 * Calcula el alto de la pared en pantalla y sus límites de dibujo,
 * recortados a la ventana.
 * Retorna: nada.
 *
 * Computes the on-screen wall height and its draw bounds, clamped to
 * the window.
 * Returns: nothing.
 */
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

/*
 * Calcula el punto exacto de impacto en la pared (wall_x, en [0,1))
 * y la columna de textura correspondiente, con corrección de espejo.
 * Retorna: nada.
 *
 * Computes the exact wall hit point (wall_x, in [0,1)) and the
 * matching texture column, with mirror correction.
 * Returns: nothing.
 */
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
