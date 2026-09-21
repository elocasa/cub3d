#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

int	open_cub_file(t_game *g, const char *path);
int	parse_scene(t_game *g, const char *path);

#endif
