#include "../includes/cub3d.h"

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

static void	destroy_tex(t_game *g, t_img *t)
{
	if (t->img)
		mlx_destroy_image(g->mlx_ptr, t->img);
	t->img = NULL;
}

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

/* Cierre limpio: vale para ESC, cruz roja y errores. No hace exit si
   se llama desde el loop de error (error_exit hace exit después). */
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
