/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_they2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:42:26 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/16 13:42:35 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	if (is_config_line(line) || is_texture_line(line))
		return (0);
	i = 0;
	while (*(line + i))
	{
		if (!is_valid_map_char(*(line + i)))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_line(char *line)
{
	if (!is_map_line(line) && !is_config_line(line) && ft_strcmp(line, "\n"))
		return (0);
	return (1);
}

int	is_valid_colour_line(char *line)
{
	int	i;

	if (!line || !*line || ft_strlen(line) < 7)
		return (0);
	if ((*line != 'F' && *line != 'C') || *(line + 1) != ' ')
		return (0);
	i = 2;
	while (*(line + i) && ft_isspace(*(line + i)))
		i++;
	while (*(line + i) && ft_isdigit(*(line + i)))
		i++;
	if (!*(line + i) || *(line + i) != ',')
		return (0);
	i++;
	while (*(line + i) && ft_isdigit(*(line + i)))
		i++;
	if (!*(line + i) || *(line + i) != ',')
		return (0);
	i++;
	while (*(line + i) && ft_isdigit(*(line + i)))
		i++;
	while (*(line + i) && ft_isspace(*(line + i)))
		i++;
	return (!*(line + i));
}

int	is_valid_texture_line(char *line)
{
	int	i;

	if (!line || !*line || ft_strlen(line) < 4)
		return (0);
	i = 2;
	while (*(line + i) && ft_isspace(*(line + i)))
		i++;
	if (i == 2)
		return (0);
	while (*(line + i) && !ft_isspace(*(line + i)))
		i++;
	while (*(line + i) && ft_isspace(*(line + i)))
		i++;
	return (!*(line + i));
}
