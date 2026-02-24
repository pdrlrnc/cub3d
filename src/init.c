/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:40:55 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:40:57 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bitspp,
			&game->img.lsize, &game->img.endian);
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
	return (1);
}

void	set_2d_point(t_game *game, int x, int y)
{
	game->map2d[y][x].init = game->scene->map[y][x];
	game->map2d[y][x].x = x;
	game->map2d[y][x].y = y;
	game->map2d[y][x].pos_x = game->cont2d.x1 + x * game->grid_size;
	game->map2d[y][x].pos_y = game->cont2d.y1 + y * game->grid_size;
	if (game->scene->map[y][x] == '1')
		game->map2d[y][x].type = WALL;
	else if (game->scene->map[y][x] == '0')
		game->map2d[y][x].type = SPACE;
	else if (in(game->scene->map[y][x], "NESW"))
	{
		game->map2d[y][x].type = PERSO;
		if (game->scene->map[y][x] == 'N')
			game->perso.angle = 270;
		else if (game->scene->map[y][x] == 'E')
			game->perso.angle = 0;
		else if (game->scene->map[y][x] == 'S')
			game->perso.angle = 90;
		else if (game->scene->map[y][x] == 'W')
			game->perso.angle = 180;
	}
	else
		game->map2d[y][x].type = VOID;
}

int	init_2d_map(t_game *game)
{
	int	y;
	int	x;

	game->nb_grids = max(game->scene->map_w, game->scene->map_h);
	while (SIZE_MAP % game->nb_grids != 0)
		game->nb_grids++;
	game->grid_size = SIZE_MAP / game->nb_grids;
	game->map2d = malloc(sizeof(t_grid *) * game->nb_grids);
	y = 0;
	while (y < game->scene->map_h)
	{
		game->map2d[y] = malloc(sizeof(t_grid) * game->nb_grids);
		x = 0;
		while (x < game->scene->map_w)
			set_2d_point(game, x++, y);
		y++;
	}
	return (1);
}

int	init_perso(t_game *game)
{
	game->perso.size = SIZE_PERSO;
	game->perso.pos_x = game->cont2d.x1 + game->scene->px
		* game->grid_size + game->grid_size / 2 - (game->perso.size / 2);
	game->perso.pos_y = game->cont2d.y1 + game->scene->py
		* game->grid_size + game->grid_size / 2 - (game->perso.size / 2);
	return (1);
}
