/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diego <diego@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-09-22 14:40:24 by diego             #+#    #+#             */
/*   Updated: 2026-09-22 14:40:24 by diego            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "../minilibx-linux/mlx.h"
# include "../srcs/libft/libft.h"
# include "types.h"

# define WIN_W 1280
# define WIN_H 720
# define TEX_W 64
# define TEX_H 64

# define MOVE_SPEED 0.04
# define ROT_SPEED 0.05

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define EV_KEYPRESS 2
# define EV_KEYRELEASE 3
# define EV_DESTROY 17

typedef struct s_game
{
	t_map_data	map;
	double		*zbuffer;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_textures	textures;
	t_player	player;
	t_raycast	raycast;
	t_keys		keys;
}	t_game;

/* parsing/ (Marcos): construye la escena a partir del fichero .cub. */
# include "parsing.h"

/* init.c */
t_game	*init_game(void);
int		init_mlx(t_game *g);
void	init_player_dir(t_game *g, char orient);

/* textures.c */
int		load_all_textures(t_game *g);
t_img	*select_texture(t_game *g, t_raycast *r);
int		get_tex_pixel(t_img *t, int x, int y);

/* raycast.c */
void	cast_ray(t_game *g, int x);
void	compute_wall_bounds(t_game *g);
void	compute_tex_x(t_game *g);
int		dda_step(t_game *g, t_raycast *r);
void	perform_dda(t_game *g);

/* render.c */
void	put_pixel(t_img *img, int x, int y, int color);
void	render_frame(t_game *g);

/* input.c */
int		on_key_press(int key, void *param);
int		on_key_release(int key, void *param);
int		is_walkable(t_game *g, double x, double y);
void	try_move(t_game *g, double dx, double dy);
void	rotate_player(t_game *g, double angle);
int		game_loop(void *param);

/* cleanup.c */
int		close_game(void *param);
void	error_exit(t_game *g, const char *msg);
void	free_map(t_game *g);

#endif
