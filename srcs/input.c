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
 * Comprueba si la celda del mapa en (x, y) es transitable (dentro
 * de los límites y no es pared).
 * Retorna: 1 si se puede pisar, 0 si no.
 *
 * Checks whether the map cell at (x, y) is walkable (inside the
 * bounds and not a wall).
 * Returns: 1 if it can be walked on, 0 otherwise.
 */
static int	is_walkable(t_game *g, double x, double y)
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
static void	try_move(t_game *g, double dx, double dy)
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
static void	rotate_player(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(angle) - g->player.dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + g->player.dir_y * cos(angle);
	g->player.plane_x = g->player.plane_x * cos(angle)
		- g->player.plane_y * sin(angle);
	g->player.plane_y = old_plane_x * sin(angle) + g->player.plane_y * cos(angle);
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
		try_move(g, g->player.dir_x * MOVE_SPEED,
			g->player.dir_y * MOVE_SPEED);
	if (g->keys.s)
		try_move(g, -g->player.dir_x * MOVE_SPEED,
			-g->player.dir_y * MOVE_SPEED);
	if (g->keys.a)
		try_move(g, -g->player.plane_x * MOVE_SPEED,
			-g->player.plane_y * MOVE_SPEED);
	if (g->keys.d)
		try_move(g, g->player.plane_x * MOVE_SPEED,
			g->player.plane_y * MOVE_SPEED);
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
