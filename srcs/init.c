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
		g->player.dir_x = 0;
		g->player.dir_y = -1;
		g->player.plane_x = 0.66;
		g->player.plane_y = 0;
	}
	else if (orient == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
		g->player.plane_x = -0.66;
		g->player.plane_y = 0;
	}
	else if (orient == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = 0.66;
	}
	else
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
		g->player.plane_x = 0;
		g->player.plane_y = -0.66;
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
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	if (!g->img.addr)
		return (-1);
	g->img.width = WIN_W;
	g->img.height = WIN_H;
	g->zbuffer = (double *)ft_calloc(WIN_W, sizeof(double));
	if (!g->zbuffer)
		return (-1);
	return (0);
}
