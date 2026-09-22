/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:09:12 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:09:12 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Avanza un paso DDA, actualiza el lado golpeado y comprueba si el
 * rayo chocó con una pared ('1') o salió del mapa.
 * Retorna: 1 si salió del mapa, 0 en caso contrario.
 *
 * Advances one DDA step, updates the hit side and checks whether the
 * ray hit a wall ('1') or left the map.
 * Returns: 1 if it left the map, 0 otherwise.
 */
int	dda_step(t_game *g, t_raycast *r)
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
		return (1);
	}
	if (g->map.grid[r->map_y][r->map_x] == '1')
		r->hit = 1;
	return (0);
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
void	perform_dda(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	while (r->hit == 0)
	{
		if (dda_step(g, r))
			return ;
	}
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	if (r->perp_wall_dist < 0.0001)
		r->perp_wall_dist = 0.0001;
}
