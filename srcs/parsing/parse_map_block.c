#include "../../includes/parser_internal.h"

/*
 * Comprueba si una línea está vacía (solo espacios, tabs o nada).
 * Retorna: 1 si la línea está en blanco, 0 si no.
 *
 * Checks whether a line is empty (only spaces, tabs, or nothing).
 * Returns: 1 if the line is blank, 0 otherwise.
 */
static int	is_blank_entry(const char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}

/*
 * Descarta las líneas en blanco iniciales y finales del buffer, que
 * solo separan las cabeceras del mapa.
 * Retorna: nada; termina el programa si no queda ninguna línea.
 *
 * Drops the leading and trailing blank lines from the buffer, which
 * only separate the headers from the map.
 * Returns: nothing; exits the program if no line is left.
 */
static void	trim_edges(t_game *g, t_parser *p, int *start, int *end)
{
	*start = 0;
	while (*start < p->map_count && is_blank_entry(p->map_lines[*start]))
	{
		free(p->map_lines[*start]);
		p->map_lines[(*start)++] = NULL;
	}
	*end = p->map_count - 1;
	while (*end >= *start && is_blank_entry(p->map_lines[*end]))
	{
		free(p->map_lines[*end]);
		p->map_lines[(*end)--] = NULL;
	}
	if (*end < *start)
		parser_error(g, p, "no se encontro el mapa");
}

/*
 * Comprueba que no quede ninguna línea en blanco dentro del bloque.
 * Retorna: nada; termina el programa si encuentra alguna.
 *
 * Checks that no blank line remains inside the block.
 * Returns: nothing; exits the program if it finds one.
 */
static void	check_no_blank_inside(t_game *g, t_parser *p, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (is_blank_entry(p->map_lines[i]))
			parser_error(g, p, "linea en blanco dentro del mapa");
		i++;
	}
}

/*
 * Desplaza las líneas del rango [start, end] al principio del array.
 * Retorna: nada.
 *
 * Shifts the lines in the [start, end] range to the front of the array.
 * Returns: nothing.
 */
static void	compact_map_lines(t_parser *p, int start, int end)
{
	int	i;

	i = 0;
	while (start + i <= end)
	{
		p->map_lines[i] = p->map_lines[start + i];
		i++;
	}
	p->map_count = i;
}

/*
 * Localiza el bloque del mapa dentro de las líneas ya acumuladas,
 * recortando separadores en blanco y validando que no haya ninguno
 * dentro del propio mapa.
 * Retorna: nada.
 *
 * Locates the map block within the already accumulated lines,
 * trimming blank separators and checking none remain inside the
 * map itself.
 * Returns: nothing.
 */
void	locate_map_block(t_game *g, t_parser *p)
{
	int	start;
	int	end;

	trim_edges(g, p, &start, &end);
	check_no_blank_inside(g, p, start, end);
	compact_map_lines(p, start, end);
}
