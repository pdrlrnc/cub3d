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
	input_validation error_checker1 error_checker2 get_next_line stack reader1\
	reader2 map_normalizer are_they checkers flood_fill parser_utils _debug\
	my_mlx control main utils

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

LIBFT_DIR	= $(SRC_DIR)/libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -g -O0 -I$(INC_DIR) -Iminilibx-linux -O3
# CFLAGS		= -g -O0 -Wall -Wextra -Werror -I$(INC_DIR) -Iminilibx-linux -O3
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
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > subject_map.cub 
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > ez_map.cub 
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > broken_ez_map.cub 
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > broken_subject_map.cub
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > egg.cub
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > simple.cub
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > island.cub
	@echo "        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111 1110101 101111010001\n11111111 1111111 111111111111" >> subject_map.cub
	@echo "\n\n\n111\n101\n1N1\n111" >> ez_map.cub
	@echo "\n\n\n111\n101\n0N1\n111" >> broken_ez_map.cub
	@echo '    1111111111          111111111\n    1N00000001          100000001\n    1001111001          101111101\n    1000000001          100000001\n    1111111111          111111111' >> island.cub
	@echo "        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111 1110101 101111010001\n11111111 1111111 011111111111" >> broken_subject_map.cub
	@echo '        111111111\n      1110000000111\n     110000000000011\n    11000011111000011\n    11000N100001000011\n    11000011111000011\n     110000000000011\n      1110000000111\n        111111111' >> egg.cub
	@echo '\n\n\n1111111\n1000001\n1001101\n1000001\n1N00001\n1111111\n' >> simple.cub

	@echo  "\n\
		$(RED)            _      _____     _ $(DEF_COLOUR)\n\
		$(RED)           | |    |____ |   | |$(DEF_COLOUR)\n\
		$(RED)  ___ _   _| |__      / / __| |$(DEF_COLOUR)\n\
		$(RED) / __| | | | '_ \    \ \/  _\` |$(DEF_COLOUR)\n\
		$(RED)| (__| |_| | |_) |.___/ / (_| |$(DEF_COLOUR)\n\
		$(RED) \___|\__,_|_.__/ \____/ \__,_|$(DEF_COLOUR)\n"

$(NAME): download_mlx_linux $(OBJ) $(LIBFT_A)
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
	@$(RM) $(MLX_LIB)
	@$(RM) *.cub

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

run: re
	@./$(NAME) egg.cub

.PHONY: all clean fclean re valgrind download_mlx_linux run
