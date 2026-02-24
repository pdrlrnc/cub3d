# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 12:06:27 by pedde-so          #+#    #+#              #
#    Updated: 2026/02/14 16:20:38 by pedde-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
MLX_LIB		= mlx_linux
SRC_FILES	= \
	_debug \
	are_they1 \
	are_they2 \
	checkers \
	error_checker1 \
	error_checker2 \
	error_checker3 \
	flood_fill \
	get_next_line \
	input_validation \
	map_normalizer \
	parser_utils \
	reader1 \
	reader2 \
	stack \
	utils \
	my_mlx \
	init \
	draw2d \
	draw3d \
	control_utils \
	control \
	raycast_utils \
	raycast \
	exit \

SRC_DIR		= src

OBJ_DIR		= obj
INC_DIR		= include

LIBFT_DIR	= $(SRC_DIR)/libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

CC			= cc
# CFLAGS		= -g -O0 -I$(INC_DIR) -Iminilibx-linux -O3
CFLAGS		= -g -O0 -Wall -Wextra -Werror -I$(INC_DIR) -Iminilibx-linux -O3
RM			= rm -rf
MOVE		= mv
MAKE		= make --no-print-directory
NVIM		= ctags -R .
INCLUDE		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRC		= $(addprefix $(SRC_DIR)/, $(addsuffix .c,$(SRC_FILES)))
OBJ		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o,$(SRC_FILES)))

RED			=\033[0;31m
VIOLET		:= \033[38;5;129m
DEF_COLOUR	=\033[0m


all: $(NAME)
	@echo  "\n\
		$(RED)            _      _____     _ $(DEF_COLOUR)\n\
		$(RED)           | |    |____ |   | |$(DEF_COLOUR)\n\
		$(RED)  ___ _   _| |__      / / __| |$(DEF_COLOUR)\n\
		$(RED) / __| | | | '_ \    \ \/  _\` |$(DEF_COLOUR)\n\
		$(RED)| (__| |_| | |_) |.___/ / (_| |$(DEF_COLOUR)\n\
		$(RED) \___|\__,_|_.__/ \____/ \__,_|$(DEF_COLOUR)\n"

$(NAME): $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(INCLUDE) -o $(NAME)


$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(NVIM)

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory clean
	@$(RM) $(OBJ_DIR)
	@$(RM) tags

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory fclean
	@$(RM) $(NAME)
# 	@$(RM) $(MLX_LIB)
# 	@$(RM) *.cub

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

download_mlx_linux: fclean
	@curl https://cdn.intra.42.fr/document/document/46338/minilibx-linux.tgz -o minilibx && \
	mkdir $(MLX_LIB) && \
	tar -xvf minilibx
	cp -r minilibx-linux/* $(MLX_LIB) && \
	rm -rf minilibx minilibx-linux && \
	make all -C $(MLX_LIB)

run:
	@clear
	@make re
	@./$(NAME) maps/subject.cub

runvalgrind:
	@clear
	@make re
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) maps/subject.cub

.PHONY: all clean fclean re valgrind download_mlx_linux run runvalgrind
