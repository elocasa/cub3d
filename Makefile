NAME		= cub3D

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -Isrcs/libft
LDFLAGS		= -Lsrcs/libft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

LIBFT_DIR	= srcs/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a
MLX_CFLAGS	= -Wno-error

SRCS		= srcs/main.c \
		  srcs/stub.c \
		  srcs/init.c \
		  srcs/textures.c \
		  srcs/raycast.c \
		  srcs/render.c \
		  srcs/input.c \
		  srcs/cleanup.c \
		  srcs/parsing/parsing.c \
		  srcs/parsing/parse_open.c \
		  srcs/parsing/parser.c \
		  srcs/parsing/parse_headers.c \
		  srcs/parsing/parse_map.c \
		  srcs/parsing/parse_colors.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -f $(MLX_DIR)/Makefile.gen ]; then \
		echo "INC=/usr/include" > $(MLX_DIR)/Makefile.gen; \
		grep -v '%%%%' $(MLX_DIR)/Makefile.mk >> $(MLX_DIR)/Makefile.gen; \
	fi
	@$(MAKE) -C $(MLX_DIR) -f Makefile.gen all CC=gcc CFLAGS="$(MLX_CFLAGS)"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then $(MAKE) -C $(MLX_DIR) -f Makefile.gen clean; fi

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
