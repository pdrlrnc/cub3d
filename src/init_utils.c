/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:26:30 by pedde-so          #+#    #+#             */
/*   Updated: 2026/03/13 14:26:31 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game_cont(t_game *game)
{
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.up = 0;
	game->keys.down = 0;
	game->cont2d.x1 = PADDING_MAP;
	game->cont2d.x2 = PADDING_MAP + SIZE_MAP;
	game->cont2d.y1 = HEIGHT - PADDING_MAP - SIZE_MAP;
	game->cont2d.y2 = HEIGHT - PADDING_MAP;
	game->cont3d.x1 = 0;
	game->cont3d.x2 = WIDTH;
	game->cont3d.y1 = 0;
	game->cont3d.y2 = HEIGHT;
	game->cont3d.mid_y = (game->cont3d.y1 + game->cont3d.y2) / 2;
	game->nb_rays = game->cont3d.x2 - game->cont3d.x1;
	game->minimap_active = 1;
	game->fisheye = 0;
	return (1);
}
