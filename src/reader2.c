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

int	read_map(t_scene **scene, t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		while (is_config_line((char *)list->content))
			list = list->next;
		if ((*scene)->map_w == -1)
		{
			read_width_and_height(scene, list);
			(*scene)->map = malloc(sizeof(char *) * ((*scene)->map_h + 1));
			check_double_ptr(*scene, (*scene)->map);
		}
		(*scene)->map[i] = normalize_line(
				(char *) list->content, (*scene)->map_w);
		(*scene)->py = i;
		read_player_position(scene, (char *) list->content);
		i++;
		list = list->next;
	}
	(*scene)->map[i] = NULL;
	ft_splitfree(normalize_map(scene));
	return (1);
}

void	read_player_position(t_scene **scene, char *line)
{
	if (!ft_strchr(line, 'N') && !ft_strchr(line, 'S')
		&& !ft_strchr(line, 'E') && !ft_strchr(line, 'W'))
		return ;
	if ((*scene)->spawn_direction == ERR)
		(*scene)->is_valid = 0;
	if ((*scene)->is_valid && ft_strchr(line, 'N'))
	{
		(*scene)->spawn_direction = NO;
		(*scene)->px = ft_strchr(line, 'N') - line;
	}
	else if ((*scene)->is_valid && ft_strchr(line, 'S'))
	{
		(*scene)->spawn_direction = SO;
		(*scene)->px = ft_strchr(line, 'S') - line;
	}
	else if ((*scene)->is_valid && ft_strchr(line, 'E'))
	{
		(*scene)->spawn_direction = EA;
		(*scene)->px = ft_strchr(line, 'E') - line;
	}
	else if ((*scene)->is_valid && ft_strchr(line, 'W'))
	{
		(*scene)->spawn_direction = WE;
		(*scene)->px = ft_strchr(line, 'W') - line;
	}
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
