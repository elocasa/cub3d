#include "../include/cub3d.h"

voidexit_error(t_game *game, const char *msg)
{
if (msg)
fprintf(stderr, "Error\n%s\n", msg);
if (game)
on_close(game);
exit(1);
}

voidfree_split(char **split)
{
inti;

i = 0;
if (!split)
return ;
while (split[i])
free(split[i++]);
free(split);
}

intis_space(char c)
{
return (c == ' ' || (c >= 9 && c <= 13));
}

char*str_trim_spaces(const char *s)
{
intstart;
intend;
char*out;

start = 0;
while (s[start] && is_space(s[start]))
start++;
end = (int)strlen(s) - 1;
while (end >= start && is_space(s[end]))
end--;
out = malloc((end - start + 2) * sizeof(char));
if (!out)
return (NULL);
memcpy(out, s + start, end - start + 1);
out[end - start + 1] = '\0';
return (out);
}
