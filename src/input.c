#include "../include/cub3d.h"

inton_key_press(int keycode, t_game *game)
{
if (keycode == 65307)
on_close(game);
else if (keycode == 'w')
game->input.w = 1;
else if (keycode == 'a')
game->input.a = 1;
else if (keycode == 's')
game->input.s = 1;
else if (keycode == 'd')
game->input.d = 1;
else if (keycode == 65361)
game->input.left = 1;
else if (keycode == 65363)
game->input.right = 1;
return (0);
}

inton_key_release(int keycode, t_game *game)
{
if (keycode == 'w')
game->input.w = 0;
else if (keycode == 'a')
game->input.a = 0;
else if (keycode == 's')
game->input.s = 0;
else if (keycode == 'd')
game->input.d = 0;
else if (keycode == 65361)
game->input.left = 0;
else if (keycode == 65363)
game->input.right = 0;
return (0);
}
