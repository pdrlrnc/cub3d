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

static void	init_ray_dir(t_ray *r, t_game *game)
{
	double	rel_x;
	double	rel_y;

	rel_x = r->px - game->cont2d.x1;
	rel_y = r->py - game->cont2d.y1;
	r->step_x = 1;
	r->side_x = ((r->map_x + 1) * game->grid_size - rel_x)
		/ game->grid_size * r->delta_x;
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (rel_x - r->map_x * game->grid_size)
			/ game->grid_size * r->delta_x;
	}
	r->step_y = 1;
	r->side_y = ((r->map_y + 1) * game->grid_size - rel_y)
		/ game->grid_size * r->delta_y;
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (rel_y - r->map_y * game->grid_size)
			/ game->grid_size * r->delta_y;
	}
}

static void	init_ray(t_ray *r, t_game *game, double angle)
{
	double	rad;

	rad = angle * M_PI / 180;
	r->px = game->player.pos_x + game->player.size / 2.0;
	r->py = game->player.pos_y + game->player.size / 2.0;
	r->dir_x = cos(rad);
	r->dir_y = sin(rad);
	r->map_x = ((r->px - game->cont2d.x1) / game->grid_size);
	r->map_y = ((r->py - game->cont2d.y1) / game->grid_size);
	r->delta_x = fabs(game->grid_size / r->dir_x);
	r->delta_y = fabs(game->grid_size / r->dir_y);
	init_ray_dir(r, game);
}

static void	step_ray(t_ray *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

int	cast_ray_dda(t_game *game, double angle, double *dist)
{
	t_ray	r;

	init_ray(&r, game, angle);
	while (1)
	{
		step_ray(&r);
		if (r.map_x < 0 || r.map_x >= game->scene->map_w
			|| r.map_y < 0 || r.map_y >= game->scene->map_h)
			break ;
		if (game->map2d[r.map_y][r.map_x].type == WALL)
			break ;
	}
	if (r.side == 0)
		*dist = r.side_x - r.delta_x;
	else
		*dist = r.side_y - r.delta_y;

	if (r.side == 0)
	{
		*dist = r.side_x - r.delta_x;
		game->wall_x = r.py + (*dist) * r.dir_y;
	}
	else
	{
		*dist = r.side_y - r.delta_y;
		game->wall_x = r.px + (*dist) * r.dir_x;
	}
	game->wall_x = game->wall_x / game->grid_size;
	game->wall_x -= floor(game->wall_x);
	game->last_ray = r;
	return (r.side);
}
