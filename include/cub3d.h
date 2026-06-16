#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <mlx.h>

# define WIN_W 1280
# define WIN_H 720
# define TEX_SIZE 64

enum e_tex_id
{
TEX_NO,
TEX_SO,
TEX_WE,
TEX_EA
};

typedef struct s_img
{
void*ptr;
int*data;
intbpp;
intsize_line;
intendian;
intwidth;
intheight;
}t_img;

typedef struct s_config
{
char*tex_path[4];
intfloor_color;
intceil_color;
char**map;
intmap_w;
intmap_h;
intplayer_x;
intplayer_y;
charplayer_dir;
}t_config;

typedef struct s_player
{
doublex;
doubley;
doubledir_x;
doubledir_y;
doubleplane_x;
doubleplane_y;
doublemove_speed;
doublerot_speed;
}t_player;

typedef struct s_input
{
intw;
inta;
ints;
intd;
intleft;
intright;
}t_input;

typedef struct s_game
{
void*mlx;
void*win;
t_imgframe;
t_imgtextures[4];
t_configcfg;
t_playerplayer;
t_inputinput;
}t_game;

voidexit_error(t_game *game, const char *msg);
voidfree_split(char **split);
voidfree_config(t_config *cfg);
intis_space(char c);
char*str_trim_spaces(const char *s);

voidparse_cub_file(t_game *game, const char *path);
voidvalidate_map(t_game *game);

voidinit_game(t_game *game);
voidload_textures(t_game *game);
void	render_frame(t_game *game);
int		render_loop(t_game *game);
int		on_key_press(int keycode, t_game *game);
int		on_key_release(int keycode, t_game *game);
int		on_close(t_game *game);

#endif
