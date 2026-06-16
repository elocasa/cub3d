#include "../include/cub3d.h"

static intis_player(char c)
{
return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static intis_walkable(char c)
{
return (c == '0' || is_player(c));
}

static intis_allowed(char c)
{
return (c == '0' || c == '1' || c == ' ' || is_player(c));
}

static voidset_player_dir(t_player *p, char dir)
{
if (dir == 'N')
*p = (t_player){.dir_x = 0, .dir_y = -1, .plane_x = 0.66, .plane_y = 0};
else if (dir == 'S')
*p = (t_player){.dir_x = 0, .dir_y = 1, .plane_x = -0.66, .plane_y = 0};
else if (dir == 'E')
*p = (t_player){.dir_x = 1, .dir_y = 0, .plane_x = 0, .plane_y = 0.66};
else
*p = (t_player){.dir_x = -1, .dir_y = 0, .plane_x = 0, .plane_y = -0.66};
p->move_speed = 0.06;
p->rot_speed = 0.04;
}

static voidvalidate_cells(t_game *game)
{
intx;
inty;
intplayer_count;

y = -1;
player_count = 0;
while (++y < game->cfg.map_h)
{
x = -1;
while (++x < game->cfg.map_w)
{
if (!is_allowed(game->cfg.map[y][x]))
exit_error(game, "Map has invalid characters");
if (is_player(game->cfg.map[y][x]))
{
player_count++;
game->cfg.player_x = x;
game->cfg.player_y = y;
game->cfg.player_dir = game->cfg.map[y][x];
}
}
}
if (player_count != 1)
exit_error(game, "Map must have exactly one player start");
}

static voidcheck_closed(t_game *game)
{
intx;
inty;

y = -1;
while (++y < game->cfg.map_h)
{
x = -1;
while (++x < game->cfg.map_w)
{
if (!is_walkable(game->cfg.map[y][x]))
continue ;
if (x == 0 || y == 0 || x == game->cfg.map_w - 1 || y == game->cfg.map_h - 1)
exit_error(game, "Map is not closed");
if (game->cfg.map[y - 1][x] == ' ' || game->cfg.map[y + 1][x] == ' '
|| game->cfg.map[y][x - 1] == ' ' || game->cfg.map[y][x + 1] == ' ')
exit_error(game, "Map is not closed");
}
}
}

voidvalidate_map(t_game *game)
{
inti;

i = 0;
while (i < 4)
{
if (access(game->cfg.tex_path[i], R_OK) != 0)
exit_error(game, "Texture file not accessible");
i++;
}
validate_cells(game);
check_closed(game);
game->player.x = game->cfg.player_x + 0.5;
game->player.y = game->cfg.player_y + 0.5;
set_player_dir(&game->player, game->cfg.player_dir);
}
