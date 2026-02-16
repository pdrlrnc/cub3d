/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_they.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:36:20 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 17:36:31 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != ' ')
		return (0);
	return (1);
}

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_config_line(char *line)
{
	if (is_sky_or_floor(line) || is_texture_line(line))
		return (1);
	return (0);
}

int	is_sky_or_floor(char *line)
{
	if (*line != 'F' && *line != 'C')
		return (0);
	return (1);
}

int	is_texture_line(char *line)
{
	if (*line != 'N' && *line != 'S' && *line != 'W' && *line != 'E')
		return (0);
	return (1);
}
