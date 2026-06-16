NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Werror -O2 -MMD -MP

SRC := src/main.c src/utils.c src/free.c src/parser.c src/map_validation.c src/game.c src/render.c src/input.c
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:.o=.d)

MLX_DIR := ./minilibx-linux
MLX_FLAGS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INC := -Iinclude -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(INC) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
