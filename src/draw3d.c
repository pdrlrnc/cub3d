/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:59:13 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 17:59:15 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_wall_slice(t_game *game, double perp_dist, t_slice *s)
{
	int	screen_h;

	screen_h = game->cont3d.y2 - game->cont3d.y1;
	if (perp_dist < 0.001)
		perp_dist = 0.001;
	s->height = (game->grid_size * screen_h) / perp_dist;
	if (s->height > screen_h)
		s->height = screen_h;
	s->mid_y = (game->cont3d.y1 + game->cont3d.y2) / 2;
	s->start = s->mid_y - (s->height / 2);
	s->end = s->mid_y + (s->height / 2);
	if (s->start < game->cont3d.y1)
		s->start = game->cont3d.y1;
	if (s->end > game->cont3d.y2)
		s->end = game->cont3d.y2;
}

static void	draw_wall_col(t_game *game, int x, t_slice *s)
{
	t_tex	*tex;

	put_line(game, LINE(x, game->cont3d.y1, x, s->start, COLOR_CEILING));
	tex = get_wall_tex(game, &game->last_ray);
	draw_tex_col(game, x, s, tex);
	put_line(game, LINE(x, s->end, x, game->cont3d.y2, COLOR_FLOOR));
}

void	draw_3d_view(t_game *game, double init_angle)
{
	double	angle_step;
	int		col;
	double	perp_dist;
	t_slice	s;

	angle_step = (RAD_DIFF * 2.0) / game->nb_rays;
	col = 1;
	while (col < game->nb_rays - 1)
	{
		cast_ray_dda(
				game,
				normalize_angle(init_angle + angle_step * col),
				&perp_dist);
		if (game->fisheye == 0)
			perp_dist *= cos((RAD_DIFF - angle_step * col) * M_PI / 180);
		calc_wall_slice(game, perp_dist, &s);
		draw_wall_col(game, game->cont3d.x1 + col, &s);
		col++;
	}
}
