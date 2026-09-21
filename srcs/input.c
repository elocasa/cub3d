#include "../includes/cub3d.h"

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

/* Colisión por ejes separados: permite deslizar pegado a la pared. */
static void	try_move(t_game *g, double dx, double dy)
{
	if (is_walkable(g, g->player.pos_x + dx, g->player.pos_y))
		g->player.pos_x += dx;
	if (is_walkable(g, g->player.pos_x, g->player.pos_y + dy))
		g->player.pos_y += dy;
}

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

/* Hook de loop: movimiento suave + re-render cada frame. */
int	game_loop(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	update_player(g);
	render_frame(g);
	return (0);
}
