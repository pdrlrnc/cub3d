# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 12:06:27 by pedde-so          #+#    #+#              #
#    Updated: 2026/02/09 12:06:28 by pedde-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
SRC_FILES	= \
	cub3d input_validation error_checker get_next_line

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

LIBFT_DIR	= $(SRC_DIR)/libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

CC		= cc
CFLAGS		= -g -O0 -Wall -Wextra -Werror -I$(INC_DIR)
RM		= rm -rf
MOVE		= mv
MAKE		= make --no-print-directory
NVIM		= ctags -R .

SRC		= $(addprefix $(SRC_DIR)/, $(addsuffix .c,$(SRC_FILES)))
OBJ		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o,$(SRC_FILES)))

RED=\033[0;31m
VIOLET      := \033[38;5;129m
DEF_COLOUR=\033[0m


all: $(NAME)
	@echo "111111\n100101\n101001\n1100N1\n111111\n" > map.cub
	@echo  "\n\
		$(RED)            _      _____     _ $(DEF_COLOUR)\n\
		$(RED)           | |    |____ |   | |$(DEF_COLOUR)\n\
		$(RED)  ___ _   _| |__      / / __| |$(DEF_COLOUR)\n\
		$(RED) / __| | | | '_ \    \ \/  _\` |$(DEF_COLOUR)\n\
		$(RED)| (__| |_| | |_) |.___/ / (_| |$(DEF_COLOUR)\n\
		$(RED) \___|\__,_|_.__/ \____/ \__,_|$(DEF_COLOUR)\n"

$(NAME): $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)


$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(NVIM)

$(OBJ_DIR):
	@mkdir -p $@
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@$(RM) tags

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) *.cub

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

run: $(NAME)
	@./$(NAME)

.PHONY: all clean fclean re valgrind run
