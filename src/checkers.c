/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:22:24 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 18:22:30 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_validity(t_scene **scene)
{
	if (!(*scene)->is_valid)
		return ;
	if ((*scene)->textures.has_no != 1 || (*scene)->textures.has_so != 1
		|| (*scene)->textures.has_ea != 1 || (*scene)->textures.has_we != 1)
		add_err(scene, MISS_INPUT_1);
	if ((*scene)->floor_r == -1 || (*scene)->floor_g == -1
		|| (*scene)->floor_b == -1)
		add_err(scene, MISS_INPUT_2);
	if ((*scene)->sky_r == -1 || (*scene)->sky_g == -1 || (*scene)->sky_b == -1)
		add_err(scene, MISS_INPUT_3);
	if ((*scene)->spawn_direction == ERR)
		add_err(scene, MISS_INPUT_4);
}

void	check_line_validity(t_scene **scene, char *line)
{
	int	i;

	i = 0;
	while (*(line + i) && is_valid_map_char(*(line + i)))
		i++;
	if (*(line + i))
		add_err(scene, MAP_ERR_2);
}

void	check_colour_range(t_scene **scene)
{
	if (!(*scene)->is_valid)
		return ;
	if ((*scene)->floor_r < 0 || (*scene)->floor_r > 255)
		add_err(scene, COLOUR_ERR_1);
	else if ((*scene)->floor_g < 0 || (*scene)->floor_g > 255)
		add_err(scene, COLOUR_ERR_1);
	else if ((*scene)->floor_b < 0 || (*scene)->floor_b > 255)
		add_err(scene, COLOUR_ERR_1);
	else if ((*scene)->sky_r < 0 || (*scene)->sky_r > 255)
		add_err(scene, COLOUR_ERR_1);
	else if ((*scene)->sky_g < 0 || (*scene)->sky_g > 255)
		add_err(scene, COLOUR_ERR_1);
	else if ((*scene)->sky_b < 0 || (*scene)->sky_b > 255)
		add_err(scene, COLOUR_ERR_1);
}
