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

//input_validation.c
t_scene	*validate_input(int argc, char**argv);
t_scene	*validate_map(t_scene **scene, int map_fd);
void	get_input_values_to_list(t_scene **scene, int map_fd);
t_scene	*get_bzeroed_scene(void);
int	is_config_line(char *line);
int	is_sky_or_floor(char *line);
int	is_texture_line(char *line);
void	check_validity(t_scene **scene);
void	clean_scene(t_scene *scene);
char	*normalize_line(char *line, int map_w);
int	run_flood_fill(char **map, int width, int height);
char	**normalize_map(t_scene **scene);

//reader1.c
void	read_config_lines(t_scene **scene, t_list *list);
void	read_colours(t_scene **scene, char **split, char colour, char **splt);
void	read_texture(t_scene **scene, char **split);
void	read_texture_cont(t_scene **scene, char **split);

//reader2.c
int	read_map(t_scene **scene, t_list *list);
void	read_player_position(t_scene **scene, char *line);
void	read_width_and_height(t_scene **scene, t_list *list);

//_debug.c
void	print_wall_tex(t_wall_tex wall_tex);
void	print_direction(t_direction direction);
void	print_scene(t_scene *scene);
void	read_width_and_height(t_scene **scene, t_list *list);
void	print_map(char **map);

//stack.c
int	**get_bzeroed_visited(int width, int height);
int	stack_is_empty(t_point	*stack);
t_point	*create_stack(int x, int y, int width, int height);
t_point	pop(t_point *stack, int top);
int	push(t_point *stack, int top, int x, int y);

#endif
