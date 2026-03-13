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
	int		i;
	t_coord	p1;
	t_coord	p2;
	t_line	line;

	i = 0;
	while (i <= SIZE_MAP)
	{
		p1 = _get_coord(game->cont2d.x1 + i, game->cont2d.y1);
		p2 = _get_coord(game->cont2d.x1 + i, game->cont2d.y2);
		line = _get_line(p1, p2, color);
		put_line(game, &line);
		p1 = _get_coord(game->cont2d.x1, game->cont2d.y1 + i);
		p2 = _get_coord(game->cont2d.x2, game->cont2d.y1 + i);
		line = _get_line(p1, p2, color);
		put_line(game, &line);
		i += game->grid_size;
	}
}

void	draw_2d_map(t_game *game, int color)
{
	int		x;
	int		y;
	t_coord	p1;
	t_coord	p2;
	t_line	line;

	y = 0;
	while (y < game->scene->map_h)
	{
		x = 0;
		while (x < game->scene->map_w)
		{
			if (game->map2d[y][x].type == WALL
				|| game->map2d[y][x].type == DOOR)
			{
				p1 = _get_coord(game->map2d[y][x].pos_x,
						game->map2d[y][x].pos_y);
				p2 = _get_coord(0, 0);
				line = _get_line(p1, p2, color);
				fill_square(game, &line, game->grid_size);
			}
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

	init_angle = game->player.angle - RAD_DIFF;
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
	t_coord	p1;
	t_coord	p2;
	t_line	line;

	p1 = _get_coord(game->player.pos_x, game->player.pos_y);
	p2 = _get_coord(0, 0);
	line = _get_line(p1, p2, color);
	fill_square(game, &line, game->player.size);
}
