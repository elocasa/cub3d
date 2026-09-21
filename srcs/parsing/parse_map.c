#include "../../includes/parser_internal.h"

/*
 * Duplica la capacidad del array de líneas del mapa sin usar realloc.
 * Retorna: nada; termina el programa si no hay memoria.
 *
 * Doubles the map lines array capacity without using realloc.
 * Returns: nothing; exits the program if there is no memory.
 */
static void	grow_map_lines(t_game *g, t_parser *p)
{
	char	**bigger;
	int		new_cap;
	int		i;

	new_cap = p->map_capacity * 2;
	if (new_cap == 0)
		new_cap = 8;
	bigger = (char **)malloc(sizeof(char *) * new_cap);
	if (!bigger)
		parser_error(g, p, "sin memoria para el mapa");
	i = 0;
	while (i < p->map_count)
	{
		bigger[i] = p->map_lines[i];
		i++;
	}
	free(p->map_lines);
	p->map_lines = bigger;
	p->map_capacity = new_cap;
}

/*
 * Acumula en crudo cualquier línea que no sea cabecera, incluidas las
 * líneas en blanco (se filtran después, al localizar el mapa).
 * Retorna: nada.
 *
 * Accumulates any non-header line verbatim, including blank ones
 * (filtered out later, when locating the map block).
 * Returns: nothing.
 */
void	store_map_line(t_game *g, t_parser *p, char *line)
{
	if (p->map_count >= p->map_capacity)
		grow_map_lines(g, p);
	p->map_lines[p->map_count] = line;
	p->map_count++;
}
