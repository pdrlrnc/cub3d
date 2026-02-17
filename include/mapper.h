/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:47:53 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 11:47:56 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPER_H
# define MAPPER_H

# define MALLOC_ERR "Unknown error with memory allocation\n"
# define PARSE_ERR_1 "Map content has alway to be the last in the .cub input file\n"
# define PARSE_ERR_2 "Map content can't be separated by a new line\n"
# define PARSE_ERR_3 "Unknown idenfifier found on input file\n"
# define MISS_INPUT_1 "There must be one and only one texture for each cardinal direction\n"
# define MISS_INPUT_2 "Floor rgb is invalid\n"
# define MISS_INPUT_3 "Ceiling rgb is invalid\n"
# define MISS_INPUT_4 "No player spawn given\n"
# define WEIRD_INPUT_1 "RGB is invalid\n"
# define WEIRD_INPUT_2 "Texture line is invalid\n"
# define COLOUR_ERR_1 "Each rgb for ceiling and floor should be in the rgb range [0, 255]\n"
# define MAP_ERR_1 "Map isn't valid - there is a leak somewhere\n"
# define MAP_ERR_2 "Invalid character found in the map\n"
# define MAP_ERR_3 "Multiple player spawns given - there must only be 1\n"

//input_validation.c
t_scene	*validate_input(int argc, char**argv);
t_scene	*validate_map(t_scene **scene, int map_fd);
t_scene	*get_bzeroed_scene(void);
void	clean_scene(t_scene *scene);
char	**trim_colours(t_scene **scene, char **rgb, char **original_split);
char	*normalize_line(char *line, int map_w);
char	**normalize_map(t_scene **scene);
void	check_line_validity(t_scene **scene, char *line);
char	*trim_line(t_scene **scene, char *line, int fd);

//flood_fill.c
int	run_flood_fill(t_scene **scene, char **map);
void	found_v(t_scene **scene, t_point *stack, char **map, t_point curr);
int	inside_checker(t_scene **scene, char **map);

//reader1.c
void	read_input_values_to_list(t_scene **scene, int map_fd);
void	read_config_lines(t_scene **scene, t_list *list);
void	read_colours(t_scene **scene, char **split, char colour, char **splt);
void	read_texture(t_scene **scene, char **split);
void	read_texture_cont(t_scene **scene, char **split);

//reader2.c
void	read_map(t_scene **scene, t_list *list);
void	read_player_position(t_scene **scene, char *line, int py);
void	read_width_and_height(t_scene **scene, t_list *list);
void	read_and_validate_play_pos(t_scene **scene, int pos, char *line, char p);
int	has_more_than_one_player(char *line, int i);

//are_they1.c
int	is_valid_map_char(char c);
int	is_config_line(char *line);
int	is_sky_or_floor(char *line);
int	is_texture_line(char *line);
int	is_walkable(char c);

//are_they2.c
int	is_map_line(char *line);
int	is_valid_line(char *line);

//_debug.c
void	print_wall_tex(t_wall_tex wall_tex);
void	print_direction(t_direction direction);
void	print_scene(t_scene *scene);
void	read_width_and_height(t_scene **scene, t_list *list);
void	print_map(char **map);

//error_checker1.c
void	check_malloc(void *ptr, void *to_free, int fd);
void	check_colour_double_ptr(t_scene *scene, char **ptr, char **old_split);
void	check_double_ptr(t_scene *scene, char **ptr);
void	check_texture_ptr(t_scene *scene, char *ptr, char **split);
void	check_inp_vals_ptr(t_scene *scene, t_list *list, int fd);

//error_checker2.c
void	check_stack_fl_fi(t_scene *scene, t_point *stack, char **map);
void	check_norm_ptr(t_scene *scene, char **map, char *ptr, int i);
void	add_err(t_scene **scene, char *err_mess);
void	print_err(t_scene *scene);
void	check_colour_trim_ptr(t_scene *scene, char **res, char **rgb, char **og_split);

//error_checker3.c
void	check_line_trim_ptr(t_scene *scene, char *ptr, int fd);

//checkers.c
void	check_colour_range(t_scene **scene);
void	check_validity(t_scene **scene);
void	check_validity(t_scene **scene);

//stack.c
t_point	*create_stack(int x, int y, int width, int height);
t_point	pop(t_point *stack, int top);
int	push(t_point *stack, int top, int x, int y);

int	**get_bzeroed_visited(int width, int height);
#endif
