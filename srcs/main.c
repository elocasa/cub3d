#include "../includes/cub3d.h"

/*
 * Punto de entrada: reserva el juego, carga la escena, arranca mlx
 * y engancha los hooks de eventos antes de entrar en el bucle.
 * Retorna: 0 si el programa termina con éxito.
 *
 * Entry point: allocates the game, loads the scene, starts mlx and
 * wires the event hooks before entering the loop.
 * Returns: 0 if the program finishes successfully.
 */
int	main(void)
{
	t_game	*g;

	g = init_game();
	if (!g)
	{
		ft_putstr_fd("Error\nCould not allocate memory\n", 2);
		return (1);
	}
	if (stub_load_scene(g) < 0)
		error_exit(g, "Could not load the test scene");
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
