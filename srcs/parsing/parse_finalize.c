#include "../../includes/parser_internal.h"

/*
 * Transfiere las rutas de textura y los colores ya validados a
 * t_textures, sin duplicar memoria: mueve los punteros y los pone a
 * NULL en el parser para que no se liberen dos veces.
 * Retorna: nada.
 *
 * Transfers the already validated texture paths and colors into
 * t_textures without duplicating memory: moves the pointers and
 * nulls them out on the parser so they are not freed twice.
 * Returns: nothing.
 */
static void	finalize_textures(t_game *g, t_parser *p)
{
	g->textures.path_no = p->path_no;
	g->textures.path_so = p->path_so;
	g->textures.path_we = p->path_we;
	g->textures.path_ea = p->path_ea;
	p->path_no = NULL;
	p->path_so = NULL;
	p->path_we = NULL;
	p->path_ea = NULL;
	g->textures.color_f = p->color_f;
	g->textures.color_c = p->color_c;
}

/*
 * Transfiere el bloque del mapa ya validado y con padding a
 * t_map_data, moviendo el array de filas en vez de copiarlo.
 * Retorna: nada.
 *
 * Transfers the already validated, padded map block into
 * t_map_data, moving the row array instead of copying it.
 * Returns: nothing.
 */
static void	finalize_map(t_game *g, t_parser *p)
{
	g->map.grid = p->map_lines;
	g->map.height = p->map_count;
	g->map.width = p->map_width;
	p->map_lines = NULL;
	p->map_count = 0;
}

/*
 * Convierte la posición del jugador de fila/columna de la cuadrícula
 * a coordenadas de mundo (centro de la celda) y fija su orientación.
 * Retorna: nada.
 *
 * Converts the player's grid row/column into world coordinates (the
 * cell's center) and sets their orientation.
 * Returns: nothing.
 */
static void	finalize_player(t_game *g, t_parser *p)
{
	g->player.pos_x = p->player_col + 0.5;
	g->player.pos_y = p->player_row + 0.5;
	init_player_dir(g, p->player_orient);
}

/*
 * Vuelca todo lo validado del parser temporal a las structs
 * compartidas del juego y libera lo que no se haya transferido.
 * Retorna: nada.
 *
 * Dumps everything validated in the temporary parser into the
 * game's shared structs and frees whatever wasn't transferred.
 * Returns: nothing.
 */
void	finalize_parser(t_game *g, t_parser *p)
{
	finalize_textures(g, p);
	finalize_map(g, p);
	finalize_player(g, p);
	free_parser(p);
}
