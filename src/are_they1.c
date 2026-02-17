/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_they1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:43:03 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/16 13:43:05 by pedde-so         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (*(line + i) && *(line + i) == ' ')
		i++;
	if (*(line + i) != 'F' && *(line + i) != 'C')
		return (0);
	return (1);
}

int	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (*(line + i) && *(line + i) == ' ')
		i++;
	if (!*(line + i) || (ft_strlen(line + i) < 2))
		return (0);
	if (*(line + i) == 'N' && *(line + i + 1) == 'O')
		return (1);
	if (*(line + i) == 'S' && *(line + i + 1) == 'O')
		return (1);
	if (*(line + i) == 'E' && *(line + i + 1) == 'A')
		return (1);
	if (*(line + i) == 'W' && *(line + i + 1) == 'E')
		return (1);
	return (0);
}
