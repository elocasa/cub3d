NAME		= cub3D

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -Lsrcs/libft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

LIBFT_DIR	= srcs/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a
MLX_CFLAGS	= -Wno-error

SRCS		= srcs/main.c \
		  srcs/init.c \
		  srcs/textures.c \
		  srcs/raycast.c \
		  srcs/dda.c \
		  srcs/render.c \
		  srcs/input.c \
		  srcs/player_move.c \
		  srcs/cleanup.c \
		  srcs/parsing/parsing.c \
		  srcs/parsing/parse_open.c \
		  srcs/parsing/parser.c \
		  srcs/parsing/parse_headers.c \
		  srcs/parsing/parse_map.c \
		  srcs/parsing/parse_map_block.c \
		  srcs/parsing/parse_map_chars.c \
		  srcs/parsing/parse_player.c \
		  srcs/parsing/parse_closed_setup.c \
		  srcs/parsing/parse_closed.c \
		  srcs/parsing/parse_pad.c \
		  srcs/parsing/parse_finalize.c \
		  srcs/parsing/parse_colors.c

OBJS_DIR	= obj
OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@if OUT=$$($(MAKE) -s --no-print-directory -C $(LIBFT_DIR) 2>&1); then \
		printf "$(GREEN)Compilado: libft$(RESET)\n"; \
	else \
		printf "$(RED)Error al compilar: libft$(RESET)\n"; \
		printf "%s\n" "$$OUT"; \
		exit 1; \
	fi

$(MLX):
	@if [ ! -f $(MLX_DIR)/Makefile.gen ]; then \
		echo "INC=/usr/include" > $(MLX_DIR)/Makefile.gen; \
		grep -v '%%%%' $(MLX_DIR)/Makefile.mk >> $(MLX_DIR)/Makefile.gen; \
	fi
	@if OUT=$$($(MAKE) -s --no-print-directory -C $(MLX_DIR) -f Makefile.gen all \
		CC=gcc CFLAGS="$(MLX_CFLAGS)" 2>&1); then \
		printf "$(GREEN)Compilado: minilibx$(RESET)\n"; \
	else \
		printf "$(RED)Error al compilar: minilibx$(RESET)\n"; \
		printf "%s\n" "$$OUT"; \
		exit 1; \
	fi

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@if OUT=$$($(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) 2>&1); then \
		printf "$(GREEN)Compilado: $(NAME)$(RESET)\n"; \
	else \
		printf "$(RED)Error al compilar: $(NAME)$(RESET)\n"; \
		printf "%s\n" "$$OUT"; \
		exit 1; \
	fi

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then \
		$(MAKE) -s --no-print-directory -C $(MLX_DIR) -f Makefile.gen clean; \
	fi

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
