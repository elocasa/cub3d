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

typedef struct s_slot
{
	char	*prefix;
	int		*found;
	char	**dest;
}	t_slot;

typedef struct s_char_pos
{
	int		row;
	int		col;
	char	c;
}	t_char_pos;

typedef struct s_fill_ctx
{
	char		**visited;
	t_char_pos	*stack;
	int			top;
}	t_fill_ctx;

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
	int				player_row;
	int				player_col;
	char			player_orient;
	int				map_width;
}	t_parser;

int			open_cub_file(t_game *g, const char *path);
t_parser	*create_parser(t_game *g, const char *path);
void		free_parser(t_parser *p);
void		parser_error(t_game *g, t_parser *p, const char *msg);
int			handle_header_line(t_game *g, t_parser *p, char *line);
void		store_map_line(t_game *g, t_parser *p, char *line);
void		handle_color_header(t_game *g, t_parser *p, char *line, char kind);
void		locate_map_block(t_game *g, t_parser *p);
void		validate_map_chars(t_game *g, t_parser *p);
void		detect_player_position(t_game *g, t_parser *p);
t_fill_ctx	init_fill_ctx(t_game *g, t_parser *p);
void		free_fill_ctx(t_fill_ctx *ctx, int map_count);
void		check_map_closed(t_game *g, t_parser *p);
void		pad_map(t_game *g, t_parser *p);
void		finalize_parser(t_game *g, t_parser *p);

#endif
