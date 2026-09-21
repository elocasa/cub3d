#include "../../includes/parsing.h"

/*
 * Punto de entrada del parser: abre el fichero .cub.
 * Retorna: 0 si el fichero se pudo abrir correctamente.
 *
 * Parser entry point: opens the .cub file.
 * Returns: 0 if the file was opened successfully.
 */
int	parse_scene(t_game *g, const char *path)
{
	int	fd;

	fd = open_cub_file(g, path);
	close(fd);
	return (0);
}
