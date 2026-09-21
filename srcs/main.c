#include "../includes/cub3d.h"

int	main(void)
{
	t_game	*g;

	g = init_game();
	if (!g)
	{
		ft_putstr_fd("Error\nNo se pudo reservar memoria\n", 2);
		return (1);
	}
	if (stub_load_scene(g) < 0)
		error_exit(g, "No se pudo cargar la escena de prueba");
	if (init_mlx(g) < 0)
		error_exit(g, "No se pudo iniciar MiniLibX");
	if (load_all_textures(g) < 0)
		error_exit(g, "No se pudo cargar una textura");
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
