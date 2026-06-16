#include "../include/cub3d.h"

voidfree_config(t_config *cfg)
{
inti;

i = 0;
while (i < 4)
{
free(cfg->tex_path[i]);
i++;
}
if (cfg->map)
{
i = 0;
while (i < cfg->map_h)
free(cfg->map[i++]);
free(cfg->map);
}
}
