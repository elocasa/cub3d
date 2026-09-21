#include "../../includes/parser_internal.h"

/*
 * Comprueba si un carácter es una orientación inicial del jugador.
 * Retorna: 1 si es N, S, E o W, 0 si no.
 *
 * Checks whether a character is a player starting orientation.
 * Returns: 1 if it is N, S, E or W, 0 otherwise.
 */
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
 * Guarda la posición y orientación del jugador en la cuadrícula del
 * mapa; termina el programa si ya se había encontrado una antes.
 * Retorna: nada.
 *
 * Stores the player's grid position and orientation; exits the
 * program if one was already found before.
 * Returns: nothing.
 */
static void	record_player(t_game *g, t_parser *p, t_char_pos pos)
{
	if (p->player_orient != '\0')
		parser_error(g, p, "more than one player start position");
	p->player_row = pos.row;
	p->player_col = pos.col;
	p->player_orient = pos.c;
}

/*
 * Recorre el mapa ya validado buscando N/S/E/W y comprueba que haya
 * exactamente una posición de jugador en todo el mapa.
 * Retorna: nada; termina el programa si hay cero o más de una.
 *
 * Walks the already validated map looking for N/S/E/W and checks
 * there is exactly one player position in the whole map.
 * Returns: nothing; exits the program if there are zero or more
 * than one.
 */
void	detect_player_position(t_game *g, t_parser *p)
{
	t_char_pos	pos;

	pos.row = 0;
	while (pos.row < p->map_count)
	{
		pos.col = 0;
		while (p->map_lines[pos.row][pos.col]
			&& p->map_lines[pos.row][pos.col] != '\n'
			&& p->map_lines[pos.row][pos.col] != '\r')
		{
			pos.c = p->map_lines[pos.row][pos.col];
			if (is_player_char(pos.c))
				record_player(g, p, pos);
			pos.col++;
		}
		pos.row++;
	}
	if (p->player_orient == '\0')
		parser_error(g, p, "no player start position found");
}
