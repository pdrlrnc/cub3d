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
#define MAPPER_H


//input_validation.c
t_scene	*validate_input(int argc, char**argv);
t_scene	*validate_map(t_scene **scene, int map_fd);
void	get_input_values(t_scene **scene, int map_fd);
t_scene	*get_bzeroed_scene(void);
void	read_config_lines(t_scene **scene, t_list *list);
int	read_texture(t_scene **scene, char **split);
int	read_colours(t_scene **scene, char **split);
int	read_map(t_scene **scene, t_list *list);
void	read_width_and_height(t_scene **scene, t_list *list);
int	is_config_line(char *line);

//_debug.c
void	print_wall_tex(t_wall_tex wall_tex);
void	print_direction(t_direction direction);
void	print_scene(t_scene *scene);
void	read_width_and_height(t_scene **scene, t_list *list);


#endif
