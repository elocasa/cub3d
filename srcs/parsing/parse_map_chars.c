#include "../../includes/parser_internal.h"

typedef struct s_char_pos
{
	int		row;
	int		col;
	char	c;
}	t_char_pos;

/*
 * Comprueba si un carácter está permitido en el mapa: '0', '1',
 * espacio, o una posición inicial N/S/E/W.
 * Retorna: 1 si es válido, 0 si no.
 *
 * Checks whether a character is allowed in the map: '0', '1', a
 * space, or a starting position N/S/E/W.
 * Returns: 1 if valid, 0 otherwise.
 */
static int	is_allowed_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/*
 * Añade un entero sin signo al final de un buffer, sin usar malloc.
 * Retorna: nada.
 *
 * Appends an unsigned int to the end of a buffer, without malloc.
 * Returns: nothing.
 */
static void	append_uint(char *buf, size_t cap, unsigned int n)
{
	char	digits[12];
	int		i;
	size_t	len;

	i = 0;
	if (n == 0)
		digits[i++] = '0';
	while (n > 0)
	{
		digits[i++] = (char)('0' + n % 10);
		n /= 10;
	}
	len = ft_strlen(buf);
	while (i > 0 && len + 1 < cap)
		buf[len++] = digits[--i];
	buf[len] = '\0';
}

/*
 * Construye el mensaje con el carácter, la línea y la columna del
 * fallo, y termina el programa con él.
 * Retorna: no retorna, el programa termina.
 *
 * Builds the message with the offending character, line and column,
 * and exits the program with it.
 * Returns: never returns, the program exits.
 */
static void	report_bad_char(t_game *g, t_parser *p, t_char_pos pos)
{
	char	msg[64];
	char	cs[2];

	cs[0] = pos.c;
	cs[1] = '\0';
	ft_strlcpy(msg, "caracter de mapa invalido '", sizeof(msg));
	ft_strlcat(msg, cs, sizeof(msg));
	ft_strlcat(msg, "' en linea ", sizeof(msg));
	append_uint(msg, sizeof(msg), (unsigned int)(pos.row + 1));
	ft_strlcat(msg, ", columna ", sizeof(msg));
	append_uint(msg, sizeof(msg), (unsigned int)(pos.col + 1));
	parser_error(g, p, msg);
}

/*
 * Valida que el bloque del mapa ya localizado solo use caracteres
 * permitidos ('0', '1', espacio, N/S/E/W), carácter a carácter.
 * Retorna: nada; termina el programa si encuentra uno inválido.
 *
 * Validates that the already located map block only uses allowed
 * characters ('0', '1', space, N/S/E/W), character by character.
 * Returns: nothing; exits the program if it finds an invalid one.
 */
void	validate_map_chars(t_game *g, t_parser *p)
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
			if (!is_allowed_char(pos.c))
				report_bad_char(g, p, pos);
			pos.col++;
		}
		pos.row++;
	}
}
