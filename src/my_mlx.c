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

void	fill_square(t_game *game, t_line *l, int size)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = l->x1;
	y = l->y1;
	while (i < size)
	{
		put_line(game, LINE(
				x + i,
				y,
				x + i,
				y + size,
				l->color));
		i++;
	}
}

void	_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * (img->bitspp / 8) + y * img->lsize);
	*(unsigned int *)dst = color;
}

static void	drawh(t_game *game, t_line *l)
{
	int	dx;
	int	dy;
	int	p;
	int	dir;

	dx = l->x2 - l->x1;
	dy = l->y2 - l->y1;
	dir = 1;
	if (dy < 0)
		dir = -dir;
	dy *= dir;
	p = 2 * dy - dx;
	while (l->x1 <= l->x2)
	{
		_put_pixel(&game->img, l->x1, l->y1, l->color);
		if (p >= 0)
		{
			l->y1 += dir;
			p -= 2 * dx;
		}
		p += 2 * dy;
		l->x1++;
	}
}

static void	drawv(t_game *game, t_line *l)
{
	int	dx;
	int	dy;
	int	p;
	int	dir;

	dx = l->x2 - l->x1;
	dy = l->y2 - l->y1;
	dir = 1;
	if (dx < 0)
		dir = -dir;
	dx *= dir;
	p = 2 * dx - dy;
	while (l->y1 <= l->y2)
	{
		_put_pixel(&game->img, l->x1, l->y1, l->color);
		if (p >= 0)
		{
			l->x1 += dir;
			p -= 2 * dy;
		}
		p += 2 * dx;
		l->y1++;
	}
}

void	put_line(t_game *game, t_line *l)
{
	t_line	tmp;

	tmp = *l;
	if (abs(tmp.x2 - tmp.x1) > abs(tmp.y2 - tmp.y1))
	{
		if (tmp.x1 > tmp.x2)
			drawh(game, LINE(tmp.x2, tmp.y2, tmp.x1, tmp.y1, tmp.color));
		else
			drawh(game, &tmp);
	}
	else
	{
		if (tmp.y1 > tmp.y2)
			drawv(game, LINE(tmp.x2, tmp.y2, tmp.x1, tmp.y1, tmp.color));
		else
			drawv(game, &tmp);
	}
}
