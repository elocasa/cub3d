#include "parser_internal.h"

/*
 * Crea la estructura temporal del parser y abre el fichero .cub.
 * Retorna: puntero al parser recién creado, con el fd ya abierto.
 *
 * Creates the parser's temporary struct and opens the .cub file.
 * Returns: pointer to the newly created parser, with the fd open.
 */
t_parser	*create_parser(t_game *g, const char *path)
{
	t_parser	*p;
	int			fd;

	fd = open_cub_file(g, path);
	p = (t_parser *)ft_calloc(1, sizeof(t_parser));
	if (!p)
	{
		close(fd);
		error_exit(g, "sin memoria para el parser");
	}
	p->fd = fd;
	return (p);
}

/*
 * Consume las líneas que queden por leer para vaciar el buffer de
 * get_next_line antes de cerrar el fichero.
 * Retorna: nada.
 *
 * Reads any remaining lines to flush get_next_line's internal buffer
 * before closing the file.
 * Returns: nothing.
 */
static void	drain_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

/*
 * Libera toda la memoria propia de la estructura temporal del parser.
 * Retorna: nada.
 *
 * Frees all memory owned by the parser's temporary struct.
 * Returns: nothing.
 */
void	free_parser(t_parser *p)
{
	int	i;

	if (!p)
		return ;
	if (p->fd >= 0)
	{
		drain_fd(p->fd);
		close(p->fd);
	}
	free(p->current_line);
	free(p->path_no);
	free(p->path_so);
	free(p->path_we);
	free(p->path_ea);
	i = 0;
	while (i < p->map_count)
		free(p->map_lines[i++]);
	free(p->map_lines);
	free(p);
}

/*
 * Libera el parser temporal y delega el mensaje y la salida en error_exit.
 * Retorna: no retorna, el programa termina.
 *
 * Frees the temporary parser and delegates the message/exit to error_exit.
 * Returns: never returns, the program exits.
 */
void	parser_error(t_game *g, t_parser *p, const char *msg)
{
	free_parser(p);
	error_exit(g, msg);
}
