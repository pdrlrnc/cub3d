/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:41:14 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:41:15 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_square(t_game *game, int x, int y, int size, int color)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_line(game, x + i, y, x + i, y + size, color);
		i++;
	}
}

void	_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bitspp / 8) + y * img->lsize);
	*(unsigned int *)dst = color;
}

static void	drawh(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int		dx;
	int		dy;
	int		p;
	int		dir;

	dx = x2 - x1;
	dy = y2 - y1;
	dir = 1;
	if (dy < 0)
		dir = -dir;
	dy *= dir;
	p = 2 * dy - dx;
	while (x1 <= x2)
	{
		_put_pixel(&game->img, x1, y1, color);
		if (p >= 0)
		{
			y1 = y1 + dir;
			p = p - 2 * dx;
		}
		p = p + 2 * dy;
		x1 = x1 + 1;
	}
}

static void	drawv(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int		dx;
	int		dy;
	int		p;
	int		dir;

	dx = x2 - x1;
	dy = y2 - y1;
	dir = 1;
	if (dx < 0)
		dir = -dir;
	dx *= dir;
	p = 2 * dx - dy;
	while (y1 <= y2)
	{
		_put_pixel(&game->img, x1, y1, color);
		if (p >= 0)
		{
			x1 = x1 + dir;
			p = p - 2 * dy;
		}
		p = p + 2 * dx;
		y1 = y1 + 1;
	}
}

void	put_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	if (abs(x2 - x1) > abs(y2 - y1))
	{
		if (x1 > x2)
			drawh(game, x1, y1, x2, y2, color);
		else
			drawh(game, x1, y1, x2, y2, color);
	}
	else
	{
		if (y1 > y2)
			drawv(game, x1, y1, x2, y2, color);
		else
			drawv(game, x1, y1, x2, y2, color);
	}
}
