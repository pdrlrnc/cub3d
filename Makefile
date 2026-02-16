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
SRC_FILES	= \
	cub3d input_validation error_checker1 error_checker2 error_checker3\
	reader2 map_normalizer are_they1 are_they2 checkers flood_fill parser_utils _debug\
	get_next_line stack reader1

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
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory clean
	@$(RM) $(OBJ_DIR)
	@$(RM) tags

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory fclean
	@$(RM) $(NAME)
	@$(RM) -rf tests

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

run: $(NAME)
	@./$(NAME)

gen_cub_tests:
	@mkdir -p tests/cub
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > tests/cub/subject_map.cub 
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > tests/cub/ez_map.cub 
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > tests/cub/broken_ez_map.cub 
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > tests/cub/broken_subject_map.cub
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > tests/cub/egg.cub
	@echo "NO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\nEA ./path_to_the_east_texture\n\n\nF 220,100,0\nC 225,30,0\n\n\n" > tests/cub/island.cub
	@echo "        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111 1110101 101111010001\n11111111 1111111 111111111111" >> tests/cub/subject_map.cub
	@echo "\n\n\n111\n101\n1N1\n111" >> tests/cub/ez_map.cub
	@echo "\n\n\n111\n101\n0N1\n111" >> tests/cub/broken_ez_map.cub
	@echo '    1111111111          111111111\n    1N00000001          100000001\n    1001111001          101111101\n    1000000001          100000001\n    1111111111          111111111' >> tests/cub/island.cub
	@echo "        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111111111\n11110111111111011100000010001\n11110111111111011101010010001\n11000000110101011100000010001\n10000000000000001100000010001\n10000000000000001101010010001\n11000001110101011111011110N0111\n11110111 1110101 101111010001\n11111111 1111111 011111111111" >> tests/cub/broken_subject_map.cub
	@echo '        111111111\n      1110000000111\n     110000000000011\n    11000011111000011\n    11000N100001000011\n    11000011111000011\n     110000000000011\n      1110000000111\n        111111111' >> tests/cub/egg.cub
	@echo "NO ./textures/no.xpm" > tests/cub/valid_01_minimal.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_01_minimal.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_01_minimal.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_01_minimal.cub
	@echo "F 220,100,0" >> tests/cub/valid_01_minimal.cub
	@echo "C 225,30,0" >> tests/cub/valid_01_minimal.cub
	@echo "" >> tests/cub/valid_01_minimal.cub
	@echo "111111" >> tests/cub/valid_01_minimal.cub
	@echo "100001" >> tests/cub/valid_01_minimal.cub
	@echo "10N001" >> tests/cub/valid_01_minimal.cub
	@echo "100001" >> tests/cub/valid_01_minimal.cub
	@echo "111111" >> tests/cub/valid_01_minimal.cub
	@echo "C 10,20,30" > tests/cub/valid_02_reordered_with_blanks.cub
	@echo "" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "F 0,0,0" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "NO ./textures/no.xpm" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "1111111" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "1N00001" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "1000001" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "1111111" >> tests/cub/valid_02_reordered_with_blanks.cub
	@echo "NO     ./textures/no.xpm" > tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "SO  ./textures/so.xpm" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "WE          ./textures/we.xpm" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "F        12,  34,56" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "C  200,210,   220" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "111111" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "100001" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "1000E1" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "100001" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "111111" >> tests/cub/valid_03_extra_spaces_tokens.cub
	@echo "NO ./textures/no.xpm" > tests/cub/valid_04_rgb_edges.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_04_rgb_edges.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_04_rgb_edges.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_04_rgb_edges.cub
	@echo "F 0,0,0" >> tests/cub/valid_04_rgb_edges.cub
	@echo "C 255,255,255" >> tests/cub/valid_04_rgb_edges.cub
	@echo "" >> tests/cub/valid_04_rgb_edges.cub
	@echo "111111" >> tests/cub/valid_04_rgb_edges.cub
	@echo "1S0001" >> tests/cub/valid_04_rgb_edges.cub
	@echo "100001" >> tests/cub/valid_04_rgb_edges.cub
	@echo "111111" >> tests/cub/valid_04_rgb_edges.cub
	@echo "NO ./textures/no.xpm" > tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "F 30,60,90" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "C 90,60,30" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "    111111" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "   100001" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "   10W001" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "   100001" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "    111111" >> tests/cub/valid_05_leading_spaces_in_map.cub
	@echo "NO ./textures/no.xpm" > tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "F 1,2,3" >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "C 4,5,6" >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "" >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "111111      " >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "100001    " >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "10N001     " >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "100001    " >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "111111     " >> tests/cub/valid_06_trailing_spaces_in_map.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_15_irregular_width_map.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "F 120,120,120" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "C 30,30,30" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "111111111" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "1N000001" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "100001" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "100000001" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "111111111" >> tests/cub/invalid_15_irregular_width_map.cub
	@echo "NO ./textures/no.xpm" > tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "F 220,100,0" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "C 225,30,0" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "111111111" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "1N0000001" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "111011101" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "1   1   1" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "111111111" >> tests/cub/valid_08_spaces_inside_map_but_safe.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_16_big_maze.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_16_big_maze.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_16_big_maze.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_16_big_maze.cub
	@echo "F 80,90,100" >> tests/cub/invalid_16_big_maze.cub
	@echo "C 10,20,40" >> tests/cub/invalid_16_big_maze.cub
	@echo "" >> tests/cub/invalid_16_big_maze.cub
	@echo "1111111111111" >> tests/cub/invalid_16_big_maze.cub
	@echo "1N000000000001" >> tests/cub/invalid_16_big_maze.cub
	@echo "101111011111101" >> tests/cub/invalid_16_big_maze.cub
	@echo "100001000000001" >> tests/cub/invalid_16_big_maze.cub
	@echo "111101111011101" >> tests/cub/invalid_16_big_maze.cub
	@echo "100000000010001" >> tests/cub/invalid_16_big_maze.cub
	@echo "1111111111111" >> tests/cub/invalid_16_big_maze.cub
	@echo "NO ./textures/no.xpm" > tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "F 7,8,9" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "C 9,8,7" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "11111" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "1E001" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "10001" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "11111" >> tests/cub/valid_10_single_blank_line_between_elements.cub
	@echo "SO ./textures/so.xpm" > tests/cub/invalid_01_missing_NO.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_01_missing_NO.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_01_missing_NO.cub
	@echo "F 220,100,0" >> tests/cub/invalid_01_missing_NO.cub
	@echo "C 225,30,0" >> tests/cub/invalid_01_missing_NO.cub
	@echo "" >> tests/cub/invalid_01_missing_NO.cub
	@echo "111111" >> tests/cub/invalid_01_missing_NO.cub
	@echo "100001" >> tests/cub/invalid_01_missing_NO.cub
	@echo "10N001" >> tests/cub/invalid_01_missing_NO.cub
	@echo "100001" >> tests/cub/invalid_01_missing_NO.cub
	@echo "111111" >> tests/cub/invalid_01_missing_NO.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_02_duplicate_NO.cub
	@echo "NO ./textures/no2.xpm" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "F 220,100,0" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "C 225,30,0" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "11111" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "1N001" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "10001" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "11111" >> tests/cub/invalid_02_duplicate_NO.cub
	@echo "NX ./textures/no.xpm" > tests/cub/invalid_03_unknown_identifier.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "F 220,100,0" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "C 225,30,0" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "11111" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "1N001" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "10001" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "11111" >> tests/cub/invalid_03_unknown_identifier.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "F 256,0,0" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "C 0,0,0" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "11111" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "1N001" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "10001" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "11111" >> tests/cub/invalid_04_rgb_out_of_range.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_05_rgb_negative.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "F -1,0,0" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "C 0,0,0" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "11111" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "1N001" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "10001" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "11111" >> tests/cub/invalid_05_rgb_negative.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "F 220,100" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "C 0,0,0" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "11111" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "1N001" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "10001" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "11111" >> tests/cub/invalid_06_rgb_wrong_count.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "F 2a,0,0" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "C 0,0,0" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "11111" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "1N001" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "10001" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "11111" >> tests/cub/invalid_07_rgb_non_numeric.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "F 220,100,0 extra" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "C 0,0,0" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "11111" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "1N001" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "10001" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "11111" >> tests/cub/invalid_08_extra_tokens_after_color.cub
	@echo "NO ./textures/no.xpm" > tests/cub/ininvalid_16_map_not_last.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "F 1,2,3" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "C 4,5,6" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "11111" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "1N001" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "10001" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "11111" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "F 9,9,9" >> tests/cub/ininvalid_16_map_not_last.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_10_invalid_map_char.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "F 1,2,3" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "C 4,5,6" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "11111" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "1N201" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "10001" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "11111" >> tests/cub/invalid_10_invalid_map_char.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_11_multiple_spawns.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "F 1,2,3" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "C 4,5,6" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "111111" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "1N0001" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "1000E1" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "100001" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "111111" >> tests/cub/invalid_11_multiple_spawns.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_12_no_spawn.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_12_no_spawn.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_12_no_spawn.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_12_no_spawn.cub
	@echo "F 1,2,3" >> tests/cub/invalid_12_no_spawn.cub
	@echo "C 4,5,6" >> tests/cub/invalid_12_no_spawn.cub
	@echo "" >> tests/cub/invalid_12_no_spawn.cub
	@echo "11111" >> tests/cub/invalid_12_no_spawn.cub
	@echo "10001" >> tests/cub/invalid_12_no_spawn.cub
	@echo "10001" >> tests/cub/invalid_12_no_spawn.cub
	@echo "11111" >> tests/cub/invalid_12_no_spawn.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_13_open_map_gap.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "F 1,2,3" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "C 4,5,6" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "11111" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "1N001" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "10001" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "11001" >> tests/cub/invalid_13_open_map_gap.cub
	@echo "NO ./textures/no.xpm" > tests/cub/invalid_14_space_leak_inside.cub
	@echo "SO ./textures/so.xpm" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "WE ./textures/we.xpm" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "EA ./textures/ea.xpm" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "F 1,2,3" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "C 4,5,6" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "111111" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "1N0001" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "10 001" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "100001" >> tests/cub/invalid_14_space_leak_inside.cub
	@echo "111111" >> tests/cub/invalid_14_space_leak_inside.cub


.PHONY: all clean fclean re valgrind run
