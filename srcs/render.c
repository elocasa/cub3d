#include "../includes/cub3d.h"

/*
 * Escribe un color en el buffer de la imagen, ignorando coordenadas
 * fuera de la ventana.
 * Retorna: nada.
 *
 * Writes a color into the image buffer, ignoring coordinates outside
 * the window.
 * Returns: nothing.
 */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}

/*
 * Oscurece un color a la mitad para las caras laterales (side==1),
 * como sombreado barato.
 * Retorna: el color original si side==0, o la versión oscurecida.
 *
 * Darkens a color by half for the side faces (side==1), as a cheap
 * shading trick.
 * Returns: the original color if side==0, or the darkened version.
 */
static int	shade(int color, int side)
{
	int	r;
	int	gg;
	int	b;

	if (side == 0)
		return (color);
	r = ((color >> 16) & 0xFF) / 2;
	gg = ((color >> 8) & 0xFF) / 2;
	b = (color & 0xFF) / 2;
	return ((r << 16) | (gg << 8) | b);
}

/*
 * Dibuja la columna de pared de la pantalla x, muestreando la
 * textura según la altura calculada, y actualiza el zbuffer.
 * Retorna: nada.
 *
 * Draws the wall column for screen x, sampling the texture according
 * to the computed height, and updates the zbuffer.
 * Returns: nothing.
 */
static void	draw_column(t_game *g, int x)
{
	t_raycast	*r;
	t_img		*tex;
	int			y;
	int			tex_y;
	int			color;

	r = &g->raycast;
	tex = select_texture(g, r);
	r->step = (double)tex->height / (double)r->line_height;
	r->tex_pos = (r->draw_start - WIN_H / 2 + r->line_height / 2) * r->step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		r->tex_pos += r->step;
		color = get_tex_pixel(tex, r->tex_x, tex_y);
		put_pixel(&g->img, x, y, shade(color, r->side));
		y++;
	}
	g->zbuffer[x] = r->perp_wall_dist;
}

/*
 * Pinta el techo con el color de C en la mitad superior y el suelo
 * con el color de F en la mitad inferior.
 * Retorna: nada.
 *
 * Paints the ceiling with C's color in the top half and the floor
 * with F's color in the bottom half.
 * Returns: nothing.
 */
static void	draw_background(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&g->img, x, y, g->textures.color_c);
			x++;
		}
		y++;
	}
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&g->img, x, y, g->textures.color_f);
			x++;
		}
		y++;
	}
}

/*
 * Renderiza un frame completo: fondo, todas las columnas de pared,
 * y vuelca la imagen a la ventana.
 * Retorna: nada.
 *
 * Renders one full frame: background, every wall column, and blits
 * the image onto the window.
 * Returns: nothing.
 */
void	render_frame(t_game *g)
{
	int	x;

	draw_background(g);
	x = 0;
	while (x < WIN_W)
	{
		cast_ray(g, x);
		draw_column(g, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img.img, 0, 0);
}
