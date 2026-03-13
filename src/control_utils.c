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
	return (game->map2d[grid_y][grid_x].type == WALL
			|| game->map2d[grid_y][grid_x].type == DOOR);
}

int	can_move(t_game *game, double new_x, double new_y)
{
	double	cx;
	double	cy;

	cx = new_x + game->player.size / 2.0;
	cy = new_y + game->player.size / 2.0;
	if (is_wall_at(game, cx, cy))
		return (0);
	return (1);
}

void	move_up_down(t_game *game, double rad, double speed)
{
	double	move_x;
	double	move_y;

	move_x = cos(rad) * speed;
	move_y = sin(rad) * speed;
	if (game->keys.up)
	{
		if (can_move(game, game->player.pos_x + move_x, game->player.pos_y))
			game->player.pos_x += move_x;
		if (can_move(game, game->player.pos_x, game->player.pos_y + move_y))
			game->player.pos_y += move_y;
	}
	if (game->keys.down)
	{
		if (can_move(game, game->player.pos_x - move_x, game->player.pos_y))
			game->player.pos_x -= move_x;
		if (can_move(game, game->player.pos_x, game->player.pos_y - move_y))
			game->player.pos_y -= move_y;
	}
}

void	move_right_left(t_game *game, double rad, double speed)
{
	double	move_x;
	double	move_y;

	move_x = -sin(rad) * speed;
	move_y = cos(rad) * speed;
	if (game->keys.mright)
	{
		if (can_move(game, game->player.pos_x + move_x, game->player.pos_y))
			game->player.pos_x += move_x;
		if (can_move(game, game->player.pos_x, game->player.pos_y + move_y))
			game->player.pos_y += move_y;
	}
	if (game->keys.mleft)
	{
		if (can_move(game, game->player.pos_x - move_x, game->player.pos_y))
			game->player.pos_x -= move_x;
		if (can_move(game, game->player.pos_x, game->player.pos_y - move_y))
			game->player.pos_y -= move_y;
	}
}
