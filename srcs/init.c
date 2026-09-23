/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morcas <morcas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 13:32:36 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/09/23 12:35:11 by morcas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Reserva el t_game a cero; el mapa y las texturas los rellena
 * stub_load_scene más adelante.
 * Retorna: puntero al juego reservado, o NULL si falla.
 *
 * Allocates t_game zeroed out; the map and textures are filled in
 * later by stub_load_scene.
 * Returns: pointer to the allocated game, or NULL on failure.
 */
t_game	*init_game(void)
{
	t_game	*g;

	g = (t_game *)ft_calloc(1, sizeof(t_game));
	return (g);
}

void	set_player_dir(t_game *g, t_vec2 dir, t_vec2 plane)
{
	g->player.dir_x = dir.x;
	g->player.dir_y = dir.y;
	g->player.plane_x = plane.x;
	g->player.plane_y = plane.y;
}

/*
 * Calcula el vector dirección y el plano de cámara del jugador a
 * partir de su orientación inicial (FOV ~66°).
 * Retorna: nada.
 *
 * Computes the player's direction vector and camera plane from their
 * starting orientation (~66° FOV).
 * Returns: nothing.
 */
void	init_player_dir(t_game *g, char orient)
{
	if (orient == 'N')
	{
		set_player_dir(g, (t_vec2){0, -1}, (t_vec2){0.66, 0});
	}
	else if (orient == 'S')
	{
		set_player_dir(g, (t_vec2){0, 1}, (t_vec2){-0.66, 0});
	}
	else if (orient == 'E')
	{
		set_player_dir(g, (t_vec2){1, 0}, (t_vec2){0, 0.66});
	}
	else
	{
		set_player_dir(g, (t_vec2){-1, 0}, (t_vec2){0, -0.66});
	}
}

/*
 * Crea la conexión con mlx, la ventana y la imagen de frame
 * reutilizable, y reserva el zbuffer.
 * Retorna: 0 si todo se creó correctamente, -1 si algo falla.
 *
 * Creates the mlx connection, the window and the reusable frame
 * image, and allocates the zbuffer.
 * Returns: 0 if everything was created successfully, -1 if something
 * fails.
 */
int	init_mlx(t_game *g)
{
	g->mlx_ptr = mlx_init();
	if (!g->mlx_ptr)
		return (-1);
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, "cub3D");
	if (!g->win_ptr)
		return (-1);
	g->img.img = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	if (!g->img.img)
		return (-1);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line_len,
			&g->img.endian);
	if (!g->img.addr)
		return (-1);
	g->img.width = WIN_W;
	g->img.height = WIN_H;
	g->zbuffer = (double *)ft_calloc(WIN_W, sizeof(double));
	if (!g->zbuffer)
		return (-1);
	return (0);
}
