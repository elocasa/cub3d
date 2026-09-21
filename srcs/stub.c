#include "../includes/cub3d.h"

/* Mapa de prueba cerrado (sustituye al parser hasta que exista).
   Jugador 'N' en (3.5, 2.5). */
static const char	*g_stub[] = {
	"1111111",
	"1000001",
	"100N001",
	"1000001",
	"1111111",
	NULL,
};

static int	stub_load_map(t_game *g)
{
	int	i;

	g->map.height = 5;
	g->map.width = 7;
	g->map.grid = (char **)ft_calloc(6, sizeof(char *));
	if (!g->map.grid)
		return (-1);
	i = 0;
	while (i < 5)
	{
		g->map.grid[i] = ft_strdup(g_stub[i]);
		if (!g->map.grid[i])
			return (-1);
		i++;
	}
	return (0);
}

int	stub_load_scene(t_game *g)
{
	if (stub_load_map(g) < 0)
		return (-1);
	g->player.pos_x = 3.5;
	g->player.pos_y = 2.5;
	init_player_dir(g, 'N');
	g->textures.path_no = "textures/no.xpm";
	g->textures.path_so = "textures/so.xpm";
	g->textures.path_we = "textures/we.xpm";
	g->textures.path_ea = "textures/ea.xpm";
	g->textures.color_c = 0x87CEEB;
	g->textures.color_f = 0x8B7355;
	return (0);
}
