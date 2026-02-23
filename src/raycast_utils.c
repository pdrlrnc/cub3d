/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:40:55 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:40:57 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit(t_game *game, int pos_i_x, int pos_i_y)
{
	int	rel_x;
	int	rel_y;
	int	grid_x;
	int	grid_y;

	rel_x = pos_i_x - game->cont2d.x1;
	rel_y = pos_i_y - game->cont2d.y1;
	grid_x = rel_x / game->grid_size;
	grid_y = rel_y / game->grid_size;
	if (game->map2d[grid_y][grid_x].type == WALL)
		return (1);
	if (rel_x % game->grid_size == 0 && grid_x > 0
		&& game->map2d[grid_y][grid_x - 1].type == WALL)
		return (1);
	if (rel_y % game->grid_size == 0 && grid_y > 0
		&& game->map2d[grid_y - 1][grid_x].type == WALL)
		return (1);
	return (0);
}

double	cast_ray(t_game *game, double angle, int draw_2d)
{
	double	rad;
	double	px;
	double	py;
	double	cos_a;
	double	sin_a;
	int		i;
	double	pos_x;
	double	pos_y;

	rad = normalize_angle(angle) * M_PI / 180;
	px = game->perso.pos_x + game->perso.size / 2;
	py = game->perso.pos_y + game->perso.size / 2;
	cos_a = cos(rad);
	sin_a = sin(rad);
	i = 0;
	while (1)
	{
		pos_x = px + cos_a * i;
		pos_y = py + sin_a * i;
		if (draw_2d)
			_put_pixel(&game->img, pos_x, pos_y, 0x00FFFF00);
		if (hit(game, pos_x, pos_y))
			break ;
		i++;
	}
	return (sqrt((pos_x - px) * (pos_x - px) + (pos_y - py) * (pos_y - py)));
}

double	cast_ray_dda(t_game *game, double angle, double *dist)
{
	double	rad;
	double	px;
	double	py;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	double	step_y;
	double	rel_x;
	double	rel_y;
	int		side;

	rad = angle * M_PI / 180;
	px = game->perso.pos_x + game->perso.size / 2.0;
	py = game->perso.pos_y + game->perso.size / 2.0;
	dir_x = cos(rad);
	dir_y = sin(rad);
	map_x = ((px - game->cont2d.x1) / game->grid_size);
	map_y = ((py - game->cont2d.y1) / game->grid_size);
	delta_x = fabs(game->grid_size / dir_x);
	delta_y = fabs(game->grid_size / dir_y);
	rel_x = px - game->cont2d.x1;
	rel_y = py - game->cont2d.y1;
	if (dir_x < 0)
	{
		step_x = -1;
		side_x = (rel_x - map_x * game->grid_size)
			/ game->grid_size * delta_x;
	}
	else
	{
		step_x = 1;
		side_x = ((map_x + 1) * game->grid_size - rel_x)
			/ game->grid_size * delta_x;
	}
	if (dir_y < 0)
	{
		step_y = -1;
		side_y = (rel_y - map_y * game->grid_size)
			/ game->grid_size * delta_y;
	}
	else
	{
		step_y = 1;
		side_y = ((map_y + 1) * game->grid_size - rel_y)
			/ game->grid_size * delta_y;
	}
	while (1)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			side = 1;
		}
		if (map_x < 0 || map_x >= game->scene->map_w
			|| map_y < 0 || map_y >= game->scene->map_h)
			break ;
		if (game->map2d[map_y][map_x].type == WALL)
			break ;
	}
	if (side == 0)
		*dist = side_x - delta_x;
	else
		*dist = side_y - delta_y;
	return (side);
}
