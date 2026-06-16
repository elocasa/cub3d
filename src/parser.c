#include "../include/cub3d.h"

typedef struct s_lines
{
char**data;
intcount;
intcap;
}t_lines;

static voidpush_line(t_lines *lines, char *line)
{
char**new_data;

if (lines->count == lines->cap)
{
lines->cap = lines->cap * 2 + 8;
new_data = malloc(sizeof(char *) * lines->cap);
if (!new_data)
{
free(line);
exit(1);
}
if (lines->data)
memcpy(new_data, lines->data, sizeof(char *) * lines->count);
free(lines->data);
lines->data = new_data;
}
lines->data[lines->count++] = line;
}

static t_linesread_all_lines(const char *path)
{
FILE*fp;
t_lineslines;
char*line;
size_tn;
ssize_tr;

lines = (t_lines){0};
fp = fopen(path, "r");
if (!fp)
exit(1);
line = NULL;
n = 0;
r = getline(&line, &n, fp);
while (r != -1)
{
if (r > 0 && line[r - 1] == '\n')
line[r - 1] = '\0';
push_line(&lines, strdup(line));
r = getline(&line, &n, fp);
}
free(line);
fclose(fp);
return (lines);
}

static intparse_rgb(const char *s)
{
intr;
intg;
intb;

if (sscanf(s, "%d,%d,%d", &r, &g, &b) != 3)
return (-1);
if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
return (-1);
return ((r << 16) | (g << 8) | b);
}

static voidparse_header_line(t_game *game, const char *line)
{
char*trim;

trim = str_trim_spaces(line);
if (!trim)
exit_error(game, "Allocation failure");
if (!strncmp(trim, "NO ", 3))
game->cfg.tex_path[TEX_NO] = str_trim_spaces(trim + 3);
else if (!strncmp(trim, "SO ", 3))
game->cfg.tex_path[TEX_SO] = str_trim_spaces(trim + 3);
else if (!strncmp(trim, "WE ", 3))
game->cfg.tex_path[TEX_WE] = str_trim_spaces(trim + 3);
else if (!strncmp(trim, "EA ", 3))
game->cfg.tex_path[TEX_EA] = str_trim_spaces(trim + 3);
else if (!strncmp(trim, "F ", 2))
game->cfg.floor_color = parse_rgb(trim + 2);
else if (!strncmp(trim, "C ", 2))
game->cfg.ceil_color = parse_rgb(trim + 2);
else if (*trim)
exit_error(game, "Invalid header line");
free(trim);
}

static intheader_complete(t_config *cfg)
{
return (cfg->tex_path[TEX_NO] && cfg->tex_path[TEX_SO] && cfg->tex_path[TEX_WE]
&& cfg->tex_path[TEX_EA] && cfg->floor_color >= 0 && cfg->ceil_color >= 0);
}

static voidbuild_map(t_game *game, t_lines lines, int start)
{
inti;
intj;
intlen;

game->cfg.map_h = lines.count - start;
if (game->cfg.map_h <= 0)
exit_error(game, "Missing map data");
game->cfg.map = calloc(game->cfg.map_h, sizeof(char *));
if (!game->cfg.map)
exit_error(game, "Allocation failure");
i = 0;
while (i < game->cfg.map_h)
{
len = (int)strlen(lines.data[start + i]);
if (len > game->cfg.map_w)
game->cfg.map_w = len;
i++;
}
i = 0;
while (i < game->cfg.map_h)
{
game->cfg.map[i] = malloc(game->cfg.map_w + 1);
if (!game->cfg.map[i])
exit_error(game, "Allocation failure");
len = (int)strlen(lines.data[start + i]);
j = 0;
while (j < game->cfg.map_w)
{
if (j < len)
game->cfg.map[i][j] = lines.data[start + i][j];
else
game->cfg.map[i][j] = ' ';
j++;
}
game->cfg.map[i][j] = '\0';
i++;
}
}

voidparse_cub_file(t_game *game, const char *path)
{
t_lineslines;
inti;

lines = read_all_lines(path);
i = 0;
while (i < lines.count && !header_complete(&game->cfg))
parse_header_line(game, lines.data[i++]);
while (i < lines.count && lines.data[i][0] == '\0')
i++;
if (!header_complete(&game->cfg))
exit_error(game, "Incomplete header");
build_map(game, lines, i);
i = 0;
while (i < lines.count)
free(lines.data[i++]);
free(lines.data);
}
