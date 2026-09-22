/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_closed_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:28:04 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:28:04 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"

/*
 * Suma la longitud de todas las líneas del mapa (incluye el salto de
 * línea final de cada una).
 * Retorna: el número total de caracteres del bloque del mapa.
 *
 * Sums the length of every map line (includes each one's trailing
 * newline).
 * Returns: the total character count of the map block.
 */
static size_t	count_total_chars(t_parser *p)
{
	size_t	total;
	int		i;

	total = 0;
	i = 0;
	while (i < p->map_count)
	{
		total += ft_strlen(p->map_lines[i]);
		i++;
	}
	return (total);
}

/*
 * Libera la rejilla de "visitado": cada fila y el array de filas.
 * Retorna: nada.
 *
 * Frees the "visited" grid: each row and the row array.
 * Returns: nothing.
 */
static void	free_visited(char **visited, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(visited[i++]);
	free(visited);
}

/*
 * Reserva una rejilla de "visitado" con la misma forma dentada que
 * el mapa, una fila por línea y del mismo tamaño que ella.
 * Retorna: la rejilla reservada y puesta a cero.
 *
 * Allocates a "visited" grid with the same ragged shape as the map,
 * one row per line and the same size as it.
 * Returns: the allocated grid, zeroed out.
 */
static char	**alloc_visited(t_game *g, t_parser *p)
{
	char	**visited;
	int		i;

	visited = (char **)ft_calloc(p->map_count, sizeof(char *));
	if (!visited)
		parser_error(g, p, "out of memory for closed-map check");
	i = 0;
	while (i < p->map_count)
	{
		visited[i] = (char *)ft_calloc(ft_strlen(p->map_lines[i]) + 1, 1);
		if (!visited[i])
		{
			free_visited(visited, i);
			parser_error(g, p, "out of memory for closed-map check");
		}
		i++;
	}
	return (visited);
}

/*
 * Prepara el contexto de la inundación: rejilla de "visitado" y la
 * pila explícita, dimensionada al máximo de celdas posible.
 * Retorna: el contexto listo para usar.
 *
 * Prepares the flood-fill context: the "visited" grid and the
 * explicit stack, sized to the maximum possible number of cells.
 * Returns: the context, ready to use.
 */
t_fill_ctx	init_fill_ctx(t_game *g, t_parser *p)
{
	t_fill_ctx	ctx;

	ctx.visited = alloc_visited(g, p);
	ctx.stack = (t_char_pos *)malloc(sizeof(t_char_pos)
			* count_total_chars(p));
	if (!ctx.stack)
	{
		free_visited(ctx.visited, p->map_count);
		parser_error(g, p, "out of memory for closed-map check");
	}
	ctx.top = 0;
	return (ctx);
}

/*
 * Libera toda la memoria del contexto de la inundación.
 * Retorna: nada.
 *
 * Frees all memory owned by the flood-fill context.
 * Returns: nothing.
 */
void	free_fill_ctx(t_fill_ctx *ctx, int map_count)
{
	free_visited(ctx->visited, map_count);
	free(ctx->stack);
}
