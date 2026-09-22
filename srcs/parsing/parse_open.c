/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:29:05 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:29:05 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser_internal.h"

/*
 * Comprueba que la ruta termine en la extensión ".cub".
 * Retorna: 1 si la extensión es válida, 0 si no lo es.
 *
 * Checks whether the path ends with the ".cub" extension.
 * Returns: 1 if the extension is valid, 0 otherwise.
 */
static int	has_valid_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	if (ft_strncmp((char *)path + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

/*
 * Valida la extensión del fichero y lo abre en modo lectura.
 * Retorna: descriptor de fichero abierto; termina el programa si falla.
 *
 * Validates the file extension and opens it for reading.
 * Returns: the opened file descriptor; exits the program on failure.
 */
int	open_cub_file(t_game *g, const char *path)
{
	int	fd;

	if (!has_valid_extension(path))
		error_exit(g, "file must have a .cub extension");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(g, strerror(errno));
	return (fd);
}
