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

void	draw_3d_view(t_game *game)
{
	int		nb_rays;
	double	init_angle;
	double	angle_step;
	int		col;
	double	perp_dist;
	int		side;
	double	ray_offset;
	double	ray_angle;
	double	wall_height;
	int		cont3d_mid_y;
	int		draw_start;
	int		draw_end;
	int		draw_x;
	int		wall_color;

	nb_rays = game->cont3d.x2 - game->cont3d.x1;
	init_angle = normalize_angle(game->perso.angle - RAD_DIFF);
	angle_step = (RAD_DIFF * 2.0) / nb_rays;
	col = 1;
	while (col < nb_rays - 1)
	{
		ray_angle = normalize_angle(init_angle + angle_step * col);
		side = cast_ray_dda(game, ray_angle, &perp_dist);
		ray_offset = RAD_DIFF - angle_step * col;
		perp_dist = perp_dist * cos(ray_offset * M_PI / 180);
		if (perp_dist < 0.001)
			perp_dist = 0.001;
		wall_height = (game->grid_size
				* (game->cont3d.y2 - game->cont3d.y1)) / perp_dist;
		if (wall_height > (game->cont3d.y2 - game->cont3d.y1))
			wall_height = game->cont3d.y2 - game->cont3d.y1;
		cont3d_mid_y = (game->cont3d.y1 + game->cont3d.y2) / 2;
		draw_start = cont3d_mid_y - (int)(wall_height / 2);
		draw_end = cont3d_mid_y + (int)(wall_height / 2);
		if (draw_start < game->cont3d.y1)
			draw_start = game->cont3d.y1;
		if (draw_end > game->cont3d.y2)
			draw_end = game->cont3d.y2;
		draw_x = game->cont3d.x1 + col;
		if (side == 0)
			wall_color = 0x00AAAAAA;
		else
			wall_color = 0x00888888;
		put_line(game, draw_x, game->cont3d.y1, draw_x, draw_start, 0x00333333);
		put_line(game, draw_x, draw_start, draw_x, draw_end, wall_color);
		put_line(game, draw_x, draw_end, draw_x, game->cont3d.y2, 0x00666666);
		col++;
	}
}
