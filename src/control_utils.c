/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:55:22 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:55:23 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_at(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = ((x - game->cont2d.x1) / game->grid_size);
	grid_y = ((y - game->cont2d.y1) / game->grid_size);
	if (grid_x < 0 || grid_x >= game->scene->map_w
		|| grid_y < 0 || grid_y >= game->scene->map_h)
		return (1);
	return (game->map2d[grid_y][grid_x].type == WALL);
}

int	can_move(t_game *game, double new_x, double new_y)
{
	double	margin;
	double	cx;
	double	cy;

	margin = 2;
	cx = new_x + game->perso.size / 2.0;
	cy = new_y + game->perso.size / 2.0;
	if (is_wall_at(game, cx - margin, cy - margin))
		return (0);
	if (is_wall_at(game, cx + margin, cy - margin))
		return (0);
	if (is_wall_at(game, cx - margin, cy + margin))
		return (0);
	if (is_wall_at(game, cx + margin, cy + margin))
		return (0);
	return (1);
}
