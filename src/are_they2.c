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
