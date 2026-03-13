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
	int		i;
	int		x;
	int		y;
	t_line	line;

	i = 0;
	x = l->p1.x;
	y = l->p1.y;
	while (i < size)
	{
		line = _get_line(_get_coord(x + i, y),
				_get_coord(x + i, y + size), l->color);
		put_line(game, &line);
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

	dx = l->p2.x - l->p1.x;
	dy = l->p2.y - l->p1.y;
	dir = 1;
	if (dy < 0)
		dir = -dir;
	dy *= dir;
	p = 2 * dy - dx;
	while (l->p1.x <= l->p2.x)
	{
		_put_pixel(&game->img, l->p1.x, l->p1.y, l->color);
		if (p >= 0)
		{
			l->p1.y += dir;
			p -= 2 * dx;
		}
		p += 2 * dy;
		l->p1.x++;
	}
}

static void	drawv(t_game *game, t_line *l)
{
	int	dx;
	int	dy;
	int	p;
	int	dir;

	dx = l->p2.x - l->p1.x;
	dy = l->p2.y - l->p1.y;
	dir = 1;
	if (dx < 0)
		dir = -dir;
	dx *= dir;
	p = 2 * dx - dy;
	while (l->p1.y <= l->p2.y)
	{
		_put_pixel(&game->img, l->p1.x, l->p1.y, l->color);
		if (p >= 0)
		{
			l->p1.x += dir;
			p -= 2 * dy;
		}
		p += 2 * dx;
		l->p1.y++;
	}
}

void	put_line(t_game *game, t_line *l)
{
	t_line	tmp;
	t_line	line;

	tmp = *l;
	if (abs(tmp.p2.x - tmp.p1.x) > abs(tmp.p2.y - tmp.p1.y))
	{
		line = _get_line(_get_coord(tmp.p2.x, tmp.p2.y),
				_get_coord(tmp.p1.x, tmp.p1.y), tmp.color);
		if (tmp.p1.x > tmp.p2.x)
			drawh(game, &line);
		else
			drawh(game, &tmp);
	}
	else
	{
		line = _get_line(_get_coord(tmp.p2.x, tmp.p2.y),
				_get_coord(tmp.p1.x, tmp.p1.y), tmp.color);
		if (tmp.p1.y > tmp.p2.y)
			drawv(game, &line);
		else
			drawv(game, &tmp);
	}
}
