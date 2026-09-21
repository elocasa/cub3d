#include "../../includes/parsing.h"
#include "../../includes/parser_internal.h"

/*
 * Comprueba que las seis cabeceras (texturas y colores) aparecieran.
 * Retorna: 1 si NO, SO, WE, EA, F y C aparecieron, 0 si falta alguna.
 *
 * Checks that all six headers (textures and colors) appeared.
 * Returns: 1 if NO, SO, WE, EA, F and C all appeared, 0 if any is missing.
 */
static int	all_headers_found(t_parser *p)
{
	return (p->found.no && p->found.so && p->found.we && p->found.ea
		&& p->found.f && p->found.c);
}

/*
 * Punto de entrada del parser: lee el .cub y separa cabeceras de mapa.
 * Retorna: 0 si las cabeceras de textura se leyeron correctamente.
 *
 * Parser entry point: reads the .cub file and splits headers from the map.
 * Returns: 0 if the texture headers were read successfully.
 */
int	parse_scene(t_game *g, const char *path)
{
	t_parser	*p;
	char		*line;

	p = create_parser(g, path);
	line = get_next_line(p->fd);
	while (line)
	{
		p->line_no++;
		p->current_line = line;
		if (handle_header_line(g, p, line))
			free(line);
		else
			store_map_line(g, p, line);
		p->current_line = NULL;
		line = get_next_line(p->fd);
	}
	if (!all_headers_found(p))
		parser_error(g, p, "faltan cabeceras (NO/SO/WE/EA/F/C)");
	locate_map_block(g, p);
	validate_map_chars(g, p);
	free_parser(p);
	return (0);
}
