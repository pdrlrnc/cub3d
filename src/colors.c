/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:40:55 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:40:57 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert_rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	load_colors(t_game *game)
{
	game->floor = convert_rgb_to_hex(
			game->scene->floor_r,
			game->scene->floor_g,
			game->scene->floor_b);
	game->ceiling = convert_rgb_to_hex(
			game->scene->sky_r,
			game->scene->sky_g,
			game->scene->sky_b);
	return (1);
}
