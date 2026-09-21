#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "cub3d.h"

typedef struct s_headers_found
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_headers_found;

typedef struct s_parser
{
	int				fd;
	int				line_no;
	char			*current_line;
	t_headers_found	found;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	int				color_f;
	int				color_c;
	char			**map_lines;
	int				map_count;
	int				map_capacity;
}	t_parser;

int			open_cub_file(t_game *g, const char *path);
t_parser	*create_parser(t_game *g, const char *path);
void		free_parser(t_parser *p);
void		parser_error(t_game *g, t_parser *p, const char *msg);
int			handle_header_line(t_game *g, t_parser *p, char *line);
void		store_map_line(t_game *g, t_parser *p, char *line);
void		handle_color_header(t_game *g, t_parser *p, char *line, char kind);

#endif
