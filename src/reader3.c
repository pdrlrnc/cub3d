/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:11:58 by pedde-so          #+#    #+#             */
/*   Updated: 2026/03/14 17:11:59 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*validate_colour_or_text_line(t_scene **scene, char *line, int map_fd)
{
	if (is_sky_or_floor(line) && !is_valid_colour_line(line))
		add_err(scene, WEIRD_INPUT_1);
	if (is_texture_line(line) && !is_valid_texture_line(line))
		add_err(scene, WEIRD_INPUT_2);
	if (is_sky_or_floor(line) || is_texture_line(line))
		line = trim_line(scene, line, map_fd);
	return (line);
}

int	read_rgb_colours(t_scene **scene, char **values, char colour)
{
	if (colour == 'F' && ((*scene)->floor_r == -1))
	{
		(*scene)->has_floor_rgb = 1;
		(*scene)->floor_r = ft_atoi(values[0]);
		(*scene)->floor_g = ft_atoi(values[1]);
		(*scene)->floor_b = ft_atoi(values[2]);
		return (1);
	}
	else if (colour == 'C' && ((*scene)->sky_r == -1))
	{
		(*scene)->has_sky_rgb = 1;
		(*scene)->sky_r = ft_atoi(values[0]);
		(*scene)->sky_g = ft_atoi(values[1]);
		(*scene)->sky_b = ft_atoi(values[2]);
		return (1);
	}
	return (0);
}
