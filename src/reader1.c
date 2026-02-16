/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:28:40 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 13:28:52 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_input_values_to_list(t_scene **scene, int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (ft_strchr(line, '\n') && ft_strlen(line) > 1)
			*(line + ft_strlen(line) - 1) = '\0';
		if (!(*scene)->input_list)
		{
			(*scene)->input_list = ft_lstnew(ft_strdup(line));
			check_inp_vals_ptr(*scene, (*scene)->input_list, map_fd);
		}
		else if (ft_strlen(line) > 1)
			ft_lstadd_back(&(*scene)->input_list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
}

void	read_config_lines(t_scene **scene, t_list *list)
{
	char	**split;

	while (list && is_texture_line((char *)list->content))
	{
		split = ft_split((char *)list->content, ' ');
		check_double_ptr(*scene, split);
		if (ft_splitlen(split) != 2)
			(*scene)->is_valid = 0;
		read_texture(scene, split);
		ft_splitfree(split);
		list = list->next;
	}
	while (list && is_sky_or_floor((char *)list->content))
	{
		split = ft_split((char *)list->content, ' ');
		check_double_ptr(*scene, split);
		read_colours(scene, split, *((char *)list->content), split);
		ft_splitfree(split);
		list = list->next;
	}
}

void	read_texture(t_scene **scene, char **split)
{
	if (!(*scene)->is_valid)
		return ;
	if (!ft_strcmp(split[0], "NO"))
	{
		(*scene)->textures.tex_no = ft_strdup(split[1]);
		check_texture_ptr(*scene, (*scene)->textures.tex_no, split);
		(*scene)->textures.has_no = 1;
	}
	else if (!ft_strcmp(split[0], "SO"))
	{
		(*scene)->textures.tex_so = ft_strdup(split[1]);
		check_texture_ptr(*scene, (*scene)->textures.tex_so, split);
		(*scene)->textures.has_so = 1;
	}
	else
		read_texture_cont(scene, split);
}

void	read_texture_cont(t_scene **scene, char **split)
{
	if (!ft_strcmp(split[0], "EA"))
	{
		(*scene)->textures.tex_ea = ft_strdup(split[1]);
		check_texture_ptr(*scene, (*scene)->textures.tex_ea, split);
		(*scene)->textures.has_ea = 1;
	}
	else if (!ft_strcmp(split[0], "WE"))
	{
		(*scene)->textures.tex_we = ft_strdup(split[1]);
		check_texture_ptr(*scene, (*scene)->textures.tex_we, split);
		(*scene)->textures.has_we = 1;
	}
	else
		(*scene)->is_valid = 0;
}

void	read_colours(t_scene **scene, char **split, char colour, char **splt)
{
	char	**values;

	values = NULL;
	values = ft_split(split[1], ',');
	check_colour_double_ptr(*scene, values, splt);
	if (ft_splitlen(values) != 3 || !ft_str_isdigit(values[0])
		|| !ft_str_isdigit(values[1]) || !ft_str_isdigit(values[2]))
		(*scene)->is_valid = 0;
	else if (colour == 'F')
	{
		(*scene)->floor_r = ft_atoi(values[0]) % 255;
		(*scene)->floor_g = ft_atoi(values[1]) % 255;
		(*scene)->floor_b = ft_atoi(values[2]) % 255;
	}
	else if (colour == 'C')
	{
		(*scene)->sky_r = ft_atoi(values[0]) % 255;
		(*scene)->sky_g = ft_atoi(values[1]) % 255;
		(*scene)->sky_b = ft_atoi(values[2]) % 255;
	}
	else
		(*scene)->is_valid = 0;
	ft_splitfree(values);
}
