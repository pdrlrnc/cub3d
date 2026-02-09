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
SRC_FILES	= main

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

CC		= cc
CFLAGS		= -g -O0 -Wall -Wextra -Werror -I$(INC_DIR)
RM		= rm -rf
NVIM		= ctags -R .

SRC		= $(addprefix $(SRC_DIR)/, $(addsuffix .c,$(SRC_FILES)))
OBJ		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o,$(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(NVIM)

$(OBJ_DIR):
	@mkdir -p $@
clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) tags

fclean: clean
	@$(RM) $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

run: $(NAME)
	@./$(NAME)

.PHONY: all clean fclean re valgrind run
