NAME		= cub3D

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -Isrcs/libft -O2
LDFLAGS		= -Lsrcs/libft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm

# Soporte para entornos sin dev X11 (solo runtime .so.6).
# Se crean enlaces locales en /tmp/opencode/x11lib para el link.
XDEV_INC	= /tmp/opencode/x11dev/usr/include
XDEV_LIB	= /tmp/opencode/x11lib
ifneq ($(wildcard $(XDEV_INC)/X11/Xlib.h),)
CFLAGS		+= -I$(XDEV_INC)
LDFLAGS		:= -L$(XDEV_LIB) $(LDFLAGS)
endif

LIBFT_DIR	= srcs/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= minilibx-linux
MLX		= $(MLX_DIR)/libmlx.a
MLX_CFLAGS	= -O3 -I$(if $(wildcard $(XDEV_INC)/X11/Xlib.h),$(XDEV_INC),/usr/include) -std=gnu89 -Wno-error=implicit-function-declaration -Wno-error=implicit-int -Wno-error=return-mismatch

SRCS		= srcs/main.c \
		  srcs/stub.c \
		  srcs/init.c \
		  srcs/textures.c \
		  srcs/raycast.c \
		  srcs/render.c \
		  srcs/input.c \
		  srcs/cleanup.c \
		  srcs/parsing/parsing.c \
		  srcs/parsing/parse_open.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -f $(MLX_DIR)/Makefile.gen ]; then \
		echo "INC=$(if $(wildcard $(XDEV_INC)/X11/Xlib.h),$(XDEV_INC),/usr/include)" > $(MLX_DIR)/Makefile.gen; \
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
