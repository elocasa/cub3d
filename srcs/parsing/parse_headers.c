#include "parser_internal.h"

typedef struct s_slot
{
	char	*prefix;
	int		*found;
	char	**dest;
}	t_slot;

/*
 * Comprueba si una línea empieza exactamente por el prefijo dado.
 * Retorna: 1 si coincide, 0 si no.
 *
 * Checks whether a line starts exactly with the given prefix.
 * Returns: 1 if it matches, 0 otherwise.
 */
static int	starts_with(const char *line, const char *prefix)
{
	size_t	i;

	i = 0;
	while (prefix[i])
	{
		if (line[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}

/*
 * Guarda la ruta de una textura tras comprobar que no esté duplicada.
 * Retorna: nada; termina el programa si está repetida o vacía.
 *
 * Stores a texture path after checking it is not a duplicate header.
 * Returns: nothing; exits the program if it is repeated or empty.
 */
static void	store_texture_path(t_game *g, t_parser *p, t_slot slot,
		char *value)
{
	if (*slot.found)
		parser_error(g, p, "cabecera de textura duplicada");
	*slot.dest = ft_strtrim(value, " \t\r\n");
	if (!*slot.dest || !*(*slot.dest))
		parser_error(g, p, "ruta de textura vacia o invalida");
	*slot.found = 1;
}

/*
 * Identifica si una línea es una cabecera (NO/SO/WE/EA/F/C) y la procesa.
 * Retorna: 1 si la línea era una cabecera, 0 si no lo era.
 *
 * Identifies whether a line is a header (NO/SO/WE/EA/F/C) and handles it.
 * Returns: 1 if the line was a header, 0 otherwise.
 */
int	handle_header_line(t_game *g, t_parser *p, char *line)
{
	t_slot	slots[4];
	int		i;

	slots[0] = (t_slot){"NO ", &p->found.no, &p->path_no};
	slots[1] = (t_slot){"SO ", &p->found.so, &p->path_so};
	slots[2] = (t_slot){"WE ", &p->found.we, &p->path_we};
	slots[3] = (t_slot){"EA ", &p->found.ea, &p->path_ea};
	i = -1;
	while (++i < 4)
	{
		if (starts_with(line, slots[i].prefix))
		{
			store_texture_path(g, p, slots[i], line + 3);
			return (1);
		}
	}
	if (starts_with(line, "F ") || starts_with(line, "C "))
		return (1);
	return (0);
}
