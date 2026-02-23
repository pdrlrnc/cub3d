/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:59:08 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 17:59:09 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_2d_grid(t_game *game, int color)
{
	int	i;

	i = 0;
	while (i <= SIZE_MAP)
	{
		put_line(game, game->cont2d.x1 + i, game->cont2d.y1,
			game->cont2d.x1 + i, game->cont2d.y2, color);
		put_line(game, game->cont2d.x1, game->cont2d.y1 + i,
			game->cont2d.x2, game->cont2d.y1 + i, color);
		i += game->grid_size;
	}
}

void	draw_2d_map(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->scene->map_h)
	{
		x = 0;
		while (x < game->scene->map_w)
		{
			if (game->map2d[y][x].type == WALL)
				fill_square(game, game->map2d[y][x].pos_x,
					game->map2d[y][x].pos_y, game->grid_size, color);
			x++;
		}
		y++;
	}
}

void	draw_2d_perso_dir(t_game *game, int x, int y, int color)
{
	double	init_angle;
	double	step;
	int		j;
	double	rad;
	int		i;

	init_angle = game->perso.angle - RAD_DIFF;
	step = (RAD_DIFF * 2) / 50;
	j = 0;
	while (j < 50)
	{
		rad = normalize_angle(init_angle + step * j) * M_PI / 180;
		i = 0;
		_put_pixel(&game->img, x + cos(rad) * i, y + sin(rad) * i, color);
		while (!hit(game, x + cos(rad) * i, y + sin(rad) * i))
		{
			_put_pixel(&game->img, x + cos(rad) * i, y + sin(rad) * i, color);
			i++;
		}
		j++;
	}
}

void	draw_2d_perso(t_game *game, int color)
{
	fill_square(game, game->perso.pos_x, game->perso.pos_y,
		game->perso.size, color);
}
