#include "../includes/cub3d.h"

/*
 * Punto de entrada: valida los argumentos, reserva el juego, parsea
 * el .cub, arranca mlx y engancha los hooks antes de entrar al bucle.
 * Retorna: 0 si el programa termina con éxito.
 *
 * Entry point: validates the arguments, allocates the game, parses
 * the .cub, starts mlx and wires the hooks before entering the loop.
 * Returns: 0 if the program finishes successfully.
 */
int	main(int argc, char **argv)
{
	t_game	*g;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	g = init_game();
	if (!g)
	{
		ft_putstr_fd("Error\nCould not allocate memory\n", 2);
		return (1);
	}
	if (parse_scene(g, argv[1]) < 0)
		error_exit(g, "Could not load the map");
	if (init_mlx(g) < 0)
		error_exit(g, "Could not initialize MiniLibX");
	if (load_all_textures(g) < 0)
		error_exit(g, "Could not load a texture");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
	mlx_hook(g->win_ptr, EV_KEYPRESS, 1L << 0, (int (*)())on_key_press, g);
	mlx_hook(g->win_ptr, EV_KEYRELEASE, 1L << 1, (int (*)())on_key_release, g);
	mlx_hook(g->win_ptr, EV_DESTROY, 0, (int (*)())close_game, g);
	mlx_loop_hook(g->mlx_ptr, (int (*)())game_loop, g);
#pragma GCC diagnostic pop
	mlx_loop(g->mlx_ptr);
	return (0);
}
