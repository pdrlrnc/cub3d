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
	if (is_config_line(line) || is_texture_line(line))
		return (0);
	if (ft_strchr(line, '1') || ft_strchr(line, '0') || ft_strchr(line, ' '))
		return (1);
	return (0);
}
