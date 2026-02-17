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
	if (!(*scene)->is_valid)
		return ;
	while (is_config_line((char *)list->content)
		|| !ft_strcmp((char *)list->content, "\n"))
		list = list->next;
	while (list)
	{
		if (!ft_strcmp((char *)list->content, "\n"))
			add_err(scene, PARSE_ERR_2);
		if ((*scene)->map_w == -1)
			(read_width_and_height(scene, list),
				(*scene)->map = malloc(sizeof(char *) * ((*scene)->map_h + 1)),
				check_double_ptr(*scene, (*scene)->map));
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
		add_err(scene, MAP_ERR_3);
	(*scene)->py = py;
	if (ft_strchr(line, 'N'))
		read_and_validate_play_pos(scene, ft_strchr(line, 'N') - line,
			line, 'N');
	else if (ft_strchr(line, 'S'))
		read_and_validate_play_pos(scene, ft_strchr(line, 'S') - line,
			line, 'S');
	else if (ft_strchr(line, 'E'))
		read_and_validate_play_pos(scene, ft_strchr(line, 'E') - line,
			line, 'E');
	else if (ft_strchr(line, 'W'))
		read_and_validate_play_pos(scene,
			ft_strchr(line, 'W') - line, line, 'W');
}

void	read_and_validate_play_pos(t_scene **scene, int pos, char *line, char p)
{
	int	i;

	i = 0;
	if (has_more_than_one_player(line, i))
		add_err(scene, MAP_ERR_3);
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

int	has_more_than_one_player(char *line, int i)
{
	int	has_n;
	int	has_s;
	int	has_e;
	int	has_w;

	has_n = 0;
	has_s = 0;
	has_e = 0;
	has_w = 0;
	while (*(line + i))
	{
		if (*(line + i) == 'N')
			has_n++;
		else if (*(line + i) == 'S')
			has_s++;
		else if (*(line + i) == 'E')
			has_e++;
		else if (*(line + i) == 'W')
			has_w++;
		i++;
	}
	if ((has_n + has_s + has_e + has_w) > 1)
		return (1);
	return (0);
}
