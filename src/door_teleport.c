/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_teleport.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:19:36 by pedde-so          #+#    #+#             */
/*   Updated: 2026/03/05 17:19:45 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    try_teleport(t_game *game)
{
    int     px;
    int     py;
    int     dx;
    int     dy;
    int     dx_arr[4] = {0, 0, 1, -1};
    int     dy_arr[4] = {1, -1, 0, 0};
    int     i;

    px = (game->player.pos_x + game->player.size / 2.0
            - game->cont2d.x1) / game->grid_size;
    py = (game->player.pos_y + game->player.size / 2.0
            - game->cont2d.y1) / game->grid_size;
    if (game->map2d[py][px].type != TELEPORT)
        return ;
    i = 0;
    while (i < 4)
    {
        dx = dx_arr[i];
        dy = dy_arr[i];
        if (game->map2d[py + dy][px + dx].type == DOOR
            && game->map2d[py + dy * 2][px + dx * 2].type == TELEPORT)
        {
		game->player.pos_x = game->map2d[py + dy * 2][px + dx * 2].pos_x + (dx < 0) * (game->grid_size - game->player.size);
		game->player.pos_y = game->map2d[py + dy * 2][px + dx * 2].pos_y + (dy < 0) * (game->grid_size - game->player.size);
            return ;
        }
        i++;
    }
}
