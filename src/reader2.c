/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:44:15 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 14:44:21 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_scene **scene, t_list *list)
{
	int	i;

	i = 0;
	while (is_config_line((char *)list->content))
		list = list->next;
	while (list)
	{
		if ((*scene)->map_w == -1)
		{
			read_width_and_height(scene, list);
			(*scene)->map = malloc(sizeof(char *) * ((*scene)->map_h + 1));
			check_double_ptr(*scene, (*scene)->map);
		}
		(*scene)->map[i] = normalize_line(
				(char *) list->content, (*scene)->map_w);
		check_line_validity(scene, (char *) list->content);
		read_player_position(scene, (char *) list->content, i);
		i++;
		list = list->next;
	}
	(*scene)->map[i] = NULL;
	ft_splitfree(normalize_map(scene));
}

void	read_player_position(t_scene **scene, char *line, int py)
{
	if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S')
		&& !ft_strchr(line, 'E') && !ft_strchr(line, 'W'))
		return ;
	if ((*scene)->spawn_direction != ERR)
		(*scene)->is_valid = 0;
	(*scene)->py = py;
	if (ft_strchr(line, 'N'))
		read_and_validate_play_pos(scene, ft_strchr(line, 'N') - line,
			ft_strchr(line, 'N') + 1, 'N');
	else if (ft_strchr(line, 'S'))
		read_and_validate_play_pos(scene, ft_strchr(line, 'S') - line,
			ft_strchr(line, 'S') + 1, 'S');
	else if (ft_strchr(line, 'E'))
		read_and_validate_play_pos(scene, ft_strchr(line, 'E') - line,
			ft_strchr(line, 'E') + 1, 'E');
	else if (ft_strchr(line, 'W'))
		read_and_validate_play_pos(scene,
			ft_strchr(line, 'W') - line, ft_strchr(line, 'W') + 1, 'W');
}

void	read_and_validate_play_pos(t_scene **scene, int pos, char *line, char p)
{
	if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || ft_strchr(line, 'E')
		|| ft_strchr(line, 'W'))
		(*scene)->is_valid = 0;
	else if (p == 'N')
		(*scene)->spawn_direction = NO;
	else if (p == 'S')
		(*scene)->spawn_direction = SO;
	else if (p == 'E')
		(*scene)->spawn_direction = EA;
	else if (p == 'W')
		(*scene)->spawn_direction = WE;
	(*scene)->px = pos;
}

void	read_width_and_height(t_scene **scene, t_list *list)
{
	int	max_width;
	int	max_height;

	max_width = 0;
	max_height = 0;
	while (list)
	{
		if ((int)ft_strlen((char *)list->content) > max_width)
			max_width = ft_strlen((char *)list->content);
		max_height++;
		list = list->next;
	}
	(*scene)->map_w = max_width;
	(*scene)->map_h = max_height;
}

void	check_line_validity(t_scene **scene, char *line)
{
	int	i;

	i = 0;
	while (*(line + i) && is_valid_map_char(*(line + i)))
		i++;
	if (*(line + i))
		(*scene)->is_valid = 0;
}
