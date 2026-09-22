/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 13:32:23 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/09/22 13:33:04 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Libera la rejilla del mapa (cada fila y el array de filas).
 * Retorna: nada.
 *
 * Frees the map grid (each row and the row array).
 * Returns: nothing.
 */
void	free_map(t_game *g)
{
	int	i;

	if (!g || !g->map.grid)
		return ;
	i = 0;
	while (i < g->map.height)
	{
		free(g->map.grid[i]);
		i++;
	}
	free(g->map.grid);
	g->map.grid = NULL;
}

/*
 * Destruye la imagen de una textura si está cargada.
 * Retorna: nada.
 *
 * Destroys a texture's image if it was loaded.
 * Returns: nothing.
 */
static void	destroy_tex(t_game *g, t_img *t)
{
	if (t->img)
		mlx_destroy_image(g->mlx_ptr, t->img);
	t->img = NULL;
}

/*
 * Libera las cuatro rutas de textura si están reservadas.
 * Retorna: nada.
 *
 * Frees the four texture paths if they were allocated.
 * Returns: nothing.
 */
static void	free_texture_paths(t_game *g)
{
	if (g->textures.path_no)
		free(g->textures.path_no);
	if (g->textures.path_so)
		free(g->textures.path_so);
	if (g->textures.path_we)
		free(g->textures.path_we);
	if (g->textures.path_ea)
		free(g->textures.path_ea);
}

/*
 * Imprime el error dado, libera todo a través de close_game y
 * termina el programa.
 * Retorna: no retorna, el programa termina.
 *
 * Prints the given error, frees everything through close_game and
 * exits the program.
 * Returns: never returns, the program exits.
 */
void	error_exit(t_game *g, const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (g)
		close_game(g);
	exit(1);
}

/*
 * Cierre limpio del juego: vale para ESC, la cruz roja de la ventana
 * y los errores (error_exit ya hace exit después de llamarlo).
 * Retorna: 0 (nunca llega a retornar, el proceso termina antes).
 *
 * Clean game shutdown: used for ESC, the window's close button and
 * errors (error_exit already exits after calling it).
 * Returns: 0 (never actually reached, the process exits first).
 */
int	close_game(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g)
		exit(0);
	destroy_tex(g, &g->textures.no);
	destroy_tex(g, &g->textures.so);
	destroy_tex(g, &g->textures.we);
	destroy_tex(g, &g->textures.ea);
	free_texture_paths(g);
	if (g->img.img)
		mlx_destroy_image(g->mlx_ptr, g->img.img);
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
	}
	free_map(g);
	if (g->zbuffer)
		free(g->zbuffer);
	free(g);
	exit(0);
	return (0);
}
