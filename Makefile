########################
# VARS
########################
NAME	=	cub3d
MLX_LIB	=	mlx_linux
SRC		=	main.c src/my_mlx.c src/control.c
OBJS	=	$(SRC:.c=.o)
CC		=	cc
CFLAGS	=	-g -Wall -Wextra -Werror -I/usr/include -Iminilibx-linux -O3 
INCLUDE	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

########################
# ACTIONS
########################

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

all: download_mlx_linux $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_LIB)

re: fclean all

bonus:

download_mlx_linux: fclean
	@curl https://cdn.intra.42.fr/document/document/44598/minilibx-linux.tgz -o minilibx && \
	mkdir $(MLX_LIB) && \
	tar -xvf minilibx
	cp -r minilibx-linux/* $(MLX_LIB) && \
	rm -rf minilibx minilibx-linux && \
	make all -C $(MLX_LIB)

.PHONY: all clean fclean re bonus download_mlx_linux
