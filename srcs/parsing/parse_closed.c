/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:28:12 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:28:12 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"

/*
 * Libera el contexto de la inundación y termina el programa porque
 * el mapa no está cerrado.
 * Retorna: no retorna, el programa termina.
 *
 * Frees the flood-fill context and exits the program because the
 * map is not closed.
 * Returns: never returns, the program exits.
 */
static void	fail_not_closed(t_game *g, t_parser *p, t_fill_ctx *ctx)
{
	free_fill_ctx(ctx, p->map_count);
	parser_error(g, p, "map is not closed");
}

/*
 * Comprueba una celda vecina: una pared ('1') frena ahí; un espacio,
 * el final de línea o salirse del mapa es una fuga; el resto es
 * suelo, que se marca visitado y se apila si no lo estaba ya.
 * Retorna: nada.
 *
 * Checks one neighbour cell: a wall ('1') stops there; a space, the
 * end of the line, or going outside the map is a leak; anything else
 * is floor, marked visited and pushed if it wasn't already.
 * Returns: nothing.
 */
static void	process_neighbor(t_game *g, t_parser *p, t_fill_ctx *ctx,
		t_char_pos pos)
{
	char	c;

	if (pos.row < 0 || pos.row >= p->map_count || pos.col < 0)
		fail_not_closed(g, p, ctx);
	if ((size_t)pos.col >= ft_strlen(p->map_lines[pos.row]))
		fail_not_closed(g, p, ctx);
	c = p->map_lines[pos.row][pos.col];
	if (c == '1')
		return ;
	if (c == '\n' || c == '\r' || c == ' ')
		fail_not_closed(g, p, ctx);
	if (!ctx->visited[pos.row][pos.col])
	{
		ctx->visited[pos.row][pos.col] = 1;
		ctx->stack[ctx->top] = pos;
		ctx->top++;
	}
}

/*
 * Comprueba que el mapa esté cerrado inundando desde la posición del
 * jugador: si la inundación llega a un espacio o se sale del mapa,
 * no está cerrado. Solo cubre la zona alcanzable desde el jugador.
 * Retorna: nada; termina el programa si el mapa no está cerrado.
 *
 * Checks the map is closed by flood-filling from the player's
 * position: if the fill reaches a space or goes outside the map, it
 * is not closed. Only covers the area reachable from the player.
 * Returns: nothing; exits the program if the map is not closed.
 */
void	check_map_closed(t_game *g, t_parser *p)
{
	t_fill_ctx	ctx;
	t_char_pos	pos;

	ctx = init_fill_ctx(g, p);
	pos.row = p->player_row;
	pos.col = p->player_col;
	ctx.visited[pos.row][pos.col] = 1;
	ctx.stack[ctx.top++] = pos;
	while (ctx.top > 0)
	{
		pos = ctx.stack[--ctx.top];
		process_neighbor(g, p, &ctx, (t_char_pos){pos.row - 1, pos.col, 0});
		process_neighbor(g, p, &ctx, (t_char_pos){pos.row + 1, pos.col, 0});
		process_neighbor(g, p, &ctx, (t_char_pos){pos.row, pos.col - 1, 0});
		process_neighbor(g, p, &ctx, (t_char_pos){pos.row, pos.col + 1, 0});
	}
	free_fill_ctx(&ctx, p->map_count);
}
