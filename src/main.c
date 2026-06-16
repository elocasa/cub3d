#include "../include/cub3d.h"

static boolhas_cub_extension(const char *path)
{
const char*dot;

dot = strrchr(path, '.');
return (dot != NULL && strcmp(dot, ".cub") == 0);
}

intmain(int argc, char **argv)
{
t_gamegame;

if (argc != 2)
{
fprintf(stderr, "Usage: ./cub3D <map.cub>\n");
return (1);
}
if (!has_cub_extension(argv[1]))
{
fprintf(stderr, "Error\nMap file must have .cub extension\n");
return (1);
}
memset(&game, 0, sizeof(game));
game.cfg.floor_color = -1;
game.cfg.ceil_color = -1;
parse_cub_file(&game, argv[1]);
validate_map(&game);
init_game(&game);
load_textures(&game);
mlx_hook(game.win, 2, 1L << 0, on_key_press, &game);
mlx_hook(game.win, 3, 1L << 1, on_key_release, &game);
mlx_hook(game.win, 17, 1L << 17, on_close, &game);
mlx_loop_hook(game.mlx, render_loop, &game);
mlx_loop(game.mlx);
return (0);
}
