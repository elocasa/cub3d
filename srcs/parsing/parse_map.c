#include "../../includes/parser_internal.h"

/*
 * Comprueba si una línea solo contiene espacios, tabs o está vacía.
 * Retorna: 1 si la línea está en blanco, 0 si no.
 *
 * Checks whether a line only contains spaces, tabs, or is empty.
 * Returns: 1 if the line is blank, 0 otherwise.
 */
static int	is_blank_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}

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
 * Descarta las líneas en blanco y acumula el resto como línea del mapa.
 * Retorna: nada.
 *
 * Discards blank lines and accumulates the rest as a map line.
 * Returns: nothing.
 */
void	store_map_line(t_game *g, t_parser *p, char *line)
{
	if (is_blank_line(line))
	{
		free(line);
		return ;
	}
	if (p->map_count >= p->map_capacity)
		grow_map_lines(g, p);
	p->map_lines[p->map_count] = line;
	p->map_count++;
}
