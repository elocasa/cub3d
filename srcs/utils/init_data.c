#include "../../includes/cub3d.h"

/* Compatibilidad con código previo: envoltorio sobre init_game. */
t_game	*init_data(void)
{
	return (init_game());
}
