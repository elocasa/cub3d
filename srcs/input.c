/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcerezo- <dcerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 14:06:51 by dcerezo-          #+#    #+#             */
/*   Updated: 2026/09/22 14:14:27 by dcerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Gestiona la pulsación de una tecla: ESC cierra el juego, las de
 * movimiento/rotación activan su flag correspondiente.
 * Retorna: 0.
 *
 * Handles a key press: ESC closes the game, movement/rotation keys
 * set their matching flag.
 * Returns: 0.
 */
int	on_key_press(int key, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (key == KEY_ESC)
		close_game(g);
	if (key == KEY_W)
		g->keys.w = 1;
	else if (key == KEY_S)
		g->keys.s = 1;
	else if (key == KEY_A)
		g->keys.a = 1;
	else if (key == KEY_D)
		g->keys.d = 1;
	else if (key == KEY_LEFT)
		g->keys.left = 1;
	else if (key == KEY_RIGHT)
		g->keys.right = 1;
	return (0);
}

/*
 * Gestiona la liberación de una tecla, desactivando su flag
 * correspondiente.
 * Retorna: 0.
 *
 * Handles a key release, clearing its matching flag.
 * Returns: 0.
 */
int	on_key_release(int key, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (key == KEY_W)
		g->keys.w = 0;
	else if (key == KEY_S)
		g->keys.s = 0;
	else if (key == KEY_A)
		g->keys.a = 0;
	else if (key == KEY_D)
		g->keys.d = 0;
	else if (key == KEY_LEFT)
		g->keys.left = 0;
	else if (key == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}

/*
 * Aplica rotación y movimiento del jugador según las teclas activas
 * en el frame actual.
 * Retorna: nada.
 *
 * Applies the player's rotation and movement based on the keys
 * currently held in this frame.
 * Returns: nothing.
 */
static void	update_player(t_game *g)
{
	if (g->keys.left)
		rotate_player(g, -ROT_SPEED);
	if (g->keys.right)
		rotate_player(g, ROT_SPEED);
	if (g->keys.w)
		try_move(g, g->player.dir_x * MOVE_SPEED, g->player.dir_y * MOVE_SPEED);
	if (g->keys.s)
		try_move(g, -g->player.dir_x * MOVE_SPEED, -g->player.dir_y
			* MOVE_SPEED);
	if (g->keys.a)
		try_move(g, -g->player.plane_x * MOVE_SPEED, -g->player.plane_y
			* MOVE_SPEED);
	if (g->keys.d)
		try_move(g, g->player.plane_x * MOVE_SPEED, g->player.plane_y
			* MOVE_SPEED);
}

/*
 * Hook del bucle de mlx: actualiza el movimiento del jugador y
 * vuelve a renderizar el frame.
 * Retorna: 0.
 *
 * mlx loop hook: updates the player's movement and re-renders the
 * frame.
 * Returns: 0.
 */
int	game_loop(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	update_player(g);
	render_frame(g);
	return (0);
}
