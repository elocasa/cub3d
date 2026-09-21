#include "../includes/cub3d.h"

static int	load_xpm(t_game *g, const char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(g->mlx_ptr, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (-1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (-1);
	return (0);
}

int	load_all_textures(t_game *g)
{
	if (load_xpm(g, g->textures.path_no, &g->textures.no) < 0)
		return (-1);
	if (load_xpm(g, g->textures.path_so, &g->textures.so) < 0)
		return (-1);
	if (load_xpm(g, g->textures.path_we, &g->textures.we) < 0)
		return (-1);
	if (load_xpm(g, g->textures.path_ea, &g->textures.ea) < 0)
		return (-1);
	return (0);
}

/* Elige textura según el lado golpeado y el signo del rayo. */
t_img	*select_texture(t_game *g, t_raycast *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (&g->textures.ea);
		return (&g->textures.we);
	}
	if (r->ray_dir_y > 0)
		return (&g->textures.so);
	return (&g->textures.no);
}

/* Lee un píxel de la textura (asume 32bpp, little endian típico mlx). */
int	get_tex_pixel(t_img *t, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= t->width)
		x = t->width - 1;
	if (y >= t->height)
		y = t->height - 1;
	dst = t->addr + y * t->line_len + x * (t->bpp / 8);
	return (*(unsigned int *)dst);
}
