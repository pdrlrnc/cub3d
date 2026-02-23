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

int	render(t_game *game)
{
	ft_memset(game->img.addr, 0, WIDTH * HEIGHT * (game->img.bitspp / 8));
	draw_3d_view(game);
	draw_2d_map(game, 0x00FFFFFF);
	// draw_2d_grid(game, 0x00FF0000);
	draw_2d_perso(game, 0x00FF0000 - 20000);
	draw_2d_perso_dir(game,
		game->perso.pos_x + game->perso.size / 2,
		game->perso.pos_y + game->perso.size / 2,
		0x00FFFF00);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (1);
}

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
	return (1);
}

int	init_2d_map(t_game *game)
{
	int	nb_grids;
	int	grid_size;
	int	y;
	int	x;

	nb_grids = max(game->scene->map_w, game->scene->map_h);
	while (SIZE_MAP % nb_grids != 0)
		nb_grids++;
	game->nb_grids = nb_grids;
	grid_size = SIZE_MAP / nb_grids;
	game->grid_size = grid_size;
	game->map2d = malloc(sizeof(t_grid *) * nb_grids);
	y = 0;
	while (y < game->scene->map_h)
	{
		game->map2d[y] = malloc(sizeof(t_grid) * nb_grids);
		x = 0;
		while (x < game->scene->map_w)
		{
			game->map2d[y][x].init = game->scene->map[y][x];
			game->map2d[y][x].x = x;
			game->map2d[y][x].y = y;
			game->map2d[y][x].pos_x = game->cont2d.x1 + x * grid_size;
			game->map2d[y][x].pos_y = game->cont2d.y1 + y * grid_size;
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
			x++;
		}
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

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->scene = validate_input(argc, argv);
	if (!game->scene)
		return (__exit(game, PARSING));
	if (!init_game(game))
		return (__exit(game, INIT_GAME));
	if (!init_2d_map(game))
		return (__exit(game, INIT_MAP2D));
	if (!init_perso(game))
		return (__exit(game, INIT_PERSO));
	if (!render(game))
		return (__exit(game, RENDERING));
	listen_events(game);
	mlx_loop(game->mlx);
	__exit(game, SUCCESS);
	return (0);
}
