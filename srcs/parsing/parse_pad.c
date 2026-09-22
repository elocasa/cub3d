/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:29:40 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:29:40 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"

/*
 * Calcula la longitud visible de una línea del mapa, sin contar su
 * salto de línea final.
 * Retorna: el número de caracteres reales de la fila.
 *
 * Computes a map line's visible length, not counting its trailing
 * newline.
 * Returns: the row's real character count.
 */
static size_t	visible_len(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		i++;
	return (i);
}

/*
 * Calcula el ancho máximo entre todas las filas del mapa.
 * Retorna: la longitud visible más larga de todas las filas.
 *
 * Computes the widest visible length across all map rows.
 * Returns: the longest visible length among all rows.
 */
static size_t	compute_max_width(t_parser *p)
{
	size_t	max;
	size_t	len;
	int		i;

	max = 0;
	i = 0;
	while (i < p->map_count)
	{
		len = visible_len(p->map_lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/*
 * Crea una copia de la fila con el ancho dado: conserva su contenido
 * real y rellena el resto con espacios.
 * Retorna: la nueva fila reservada.
 *
 * Creates a copy of the row at the given width: keeps its real
 * content and fills the rest with spaces.
 * Returns: the newly allocated row.
 */
static char	*pad_row(t_game *g, t_parser *p, char *row, size_t width)
{
	char	*padded;
	size_t	len;
	size_t	i;

	len = visible_len(row);
	padded = (char *)malloc(width + 1);
	if (!padded)
		parser_error(g, p, "out of memory for map padding");
	i = 0;
	while (i < len)
	{
		padded[i] = row[i];
		i++;
	}
	while (i < width)
		padded[i++] = ' ';
	padded[width] = '\0';
	return (padded);
}

/*
 * Rellena todas las filas del mapa al mismo ancho (el de la fila más
 * larga), usando espacio como relleno, para que quede rectangular.
 * Retorna: nada.
 *
 * Pads every map row to the same width (the widest row's), using
 * space as filler, so the map becomes rectangular.
 * Returns: nothing.
 */
void	pad_map(t_game *g, t_parser *p)
{
	size_t	width;
	char	*padded;
	int		i;

	width = compute_max_width(p);
	i = 0;
	while (i < p->map_count)
	{
		padded = pad_row(g, p, p->map_lines[i], width);
		free(p->map_lines[i]);
		p->map_lines[i] = padded;
		i++;
	}
	p->map_width = (int)width;
}
