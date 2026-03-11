/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_teleport.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:54:28 by pedde-so          #+#    #+#             */
/*   Updated: 2026/03/11 17:54:29 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_dx_arr(int *dx_arr)
{
	dx_arr[0] = 0;
	dx_arr[1] = 0;
	dx_arr[2] = 1;
	dx_arr[3] = -1;
}

static void	get_dy_arr(int *dy_arr)
{
	dy_arr[0] = 1;
	dy_arr[1] = -1;
	dy_arr[2] = 0;
	dy_arr[3] = 0;
}

static void	found_tel(t_game *game, t_norm_indexes is)
{
	game->player.pos_x = game->map2d[is.j + is.l * 2][is.i + is.k * 2].pos_x
		+ (is.k < 0) * (game->grid_size - game->player.size);
	game->player.pos_y = game->map2d[is.j + is.l * 2][is.i + is.k * 2].pos_y
		+ (is.l < 0) * (game->grid_size - game->player.size);
}

void	try_teleport(t_game *game)
{
	t_norm_indexes	is;
	int				dx_arr[4];
	int				dy_arr[4];
	int				i;

	(void)is;
	get_dx_arr(dx_arr);
	get_dy_arr(dy_arr);
	is.i = (game->player.pos_x + game->player.size / 2.0
			- game->cont2d.x1) / game->grid_size;
	is.j = (game->player.pos_y + game->player.size / 2.0
			- game->cont2d.y1) / game->grid_size;
	if (game->map2d[is.j][is.i].type != TELEPORT)
		return ;
	i = 0;
	while (i < 4)
	{
		is.k = dx_arr[i];
		is.l = dy_arr[i];
		if (game->map2d[is.j + is.l][is.i + is.k].type == DOOR
			&& game->map2d[is.j + is.l * 2][is.i + is.k * 2].type == TELEPORT)
			return (found_tel(game, is));
		i++;
	}
}
