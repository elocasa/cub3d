#include "../../includes/parser_internal.h"

/*
 * Comprueba que una cadena no esté vacía y sean todo dígitos.
 * Retorna: 1 si es un número válido, 0 si no.
 *
 * Checks that a string is non-empty and made only of digits.
 * Returns: 1 if it is a valid number, 0 otherwise.
 */
static int	is_digit_token(const char *token)
{
	int	i;

	if (!token || !token[0])
		return (0);
	i = 0;
	while (token[i])
	{
		if (!ft_isdigit(token[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Convierte un token a entero y comprueba que esté entre 0 y 255.
 * Retorna: el valor del componente, o -1 si no es válido.
 *
 * Converts a token to an int and checks it is between 0 and 255.
 * Returns: the component's value, or -1 if it is not valid.
 */
static int	parse_component(const char *token)
{
	int	value;

	if (!is_digit_token(token))
		return (-1);
	value = ft_atoi(token);
	if (value > 255)
		return (-1);
	return (value);
}

/*
 * Separa "R,G,B" en tres trozos, comprobando que haya exactamente tres.
 * Retorna: array de 3 strings; termina el programa si el formato es malo.
 *
 * Splits "R,G,B" into three tokens, checking there are exactly three.
 * Returns: array of 3 strings; exits the program if the format is wrong.
 */
static char	**split_rgb_value(t_game *g, t_parser *p, char *value)
{
	char	*trimmed;
	char	**parts;

	trimmed = ft_strtrim(value, " \t\r\n");
	if (!trimmed)
		parser_error(g, p, "sin memoria para color");
	parts = ft_split(trimmed, ',');
	free(trimmed);
	if (!parts)
		parser_error(g, p, "sin memoria para color");
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_all(parts);
		parser_error(g, p, "color invalido, se esperaba R,G,B (0-255)");
	}
	return (parts);
}

/*
 * Empaqueta "R,G,B" en un int 0xRRGGBB, igual que espera render.c.
 * Retorna: el color empaquetado; termina el programa si algún valor
 * está fuera de 0-255.
 *
 * Packs "R,G,B" into a 0xRRGGBB int, matching what render.c expects.
 * Returns: the packed color; exits the program if any value is out
 * of 0-255.
 */
static int	pack_rgb(t_game *g, t_parser *p, char *value)
{
	char	**parts;
	int		rgb[3];
	int		i;

	parts = split_rgb_value(g, p, value);
	i = 0;
	while (i < 3)
	{
		rgb[i] = parse_component(parts[i]);
		if (rgb[i] < 0)
		{
			free_all(parts);
			parser_error(g, p, "componente de color invalido (0-255)");
		}
		i++;
	}
	free_all(parts);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

/*
 * Procesa una cabecera F o C: comprueba duplicados y guarda el color.
 * Retorna: nada.
 *
 * Handles an F or C header: checks for duplicates and stores the color.
 * Returns: nothing.
 */
void	handle_color_header(t_game *g, t_parser *p, char *line, char kind)
{
	int	*found;
	int	*dest;

	if (kind == 'f')
	{
		found = &p->found.f;
		dest = &p->color_f;
	}
	else
	{
		found = &p->found.c;
		dest = &p->color_c;
	}
	if (*found)
		parser_error(g, p, "cabecera de color duplicada");
	*dest = pack_rgb(g, p, line + 2);
	*found = 1;
}
