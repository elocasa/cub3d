/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:08:17 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/09/22 14:14:37 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Comprueba si la celda del mapa en (x, y) es transitable (dentro
 * de los límites y no es pared).
 * Retorna: 1 si se puede pisar, 0 si no.
 *
 * Checks whether the map cell at (x, y) is walkable (inside the
 * bounds and not a wall).
 * Returns: 1 if it can be walked on, 0 otherwise.
 */
int	is_walkable(t_game *g, double x, double y)
{
	int	cx;
	int	cy;

	cx = (int)x;
	cy = (int)y;
	if (cx < 0 || cy < 0 || cx >= g->map.width || cy >= g->map.height)
		return (0);
	return (g->map.grid[cy][cx] != '1');
}

/*
 * Intenta mover al jugador en cada eje por separado, permitiendo
 * deslizarse pegado a una pared en vez de bloquear el movimiento.
 * Retorna: nada.
 *
 * Tries to move the player on each axis separately, allowing them to
 * slide along a wall instead of blocking the movement.
 * Returns: nothing.
 */

void	try_move(t_game *g, double dx, double dy)
{
	if (is_walkable(g, g->player.pos_x + dx, g->player.pos_y))
		g->player.pos_x += dx;
	if (is_walkable(g, g->player.pos_x, g->player.pos_y + dy))
		g->player.pos_y += dy;
}

/*
 * Rota la dirección y el plano de cámara del jugador el ángulo dado.
 * Retorna: nada.
 *
 * Rotates the player's direction and camera plane by the given
 * angle.
 * Returns: nothing.
 */
void	rotate_player(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(angle) - g->player.dir_y
		* sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + g->player.dir_y * cos(angle);
	g->player.plane_x = g->player.plane_x * cos(angle) - g->player.plane_y
		* sin(angle);
	g->player.plane_y = old_plane_x * sin(angle) + g->player.plane_y
		* cos(angle);
}
