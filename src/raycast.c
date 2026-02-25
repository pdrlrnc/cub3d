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
	draw_3d_view(game, normalize_angle(game->player.angle - RAD_DIFF));
	if (game->minimap_active)
	{
		draw_2d_map(game, 0x00FFFFFF);
		// draw_2d_grid(game, 0x00FF0000);
		draw_2d_perso(game, 0x00FF0000 - 20000);
		draw_2d_perso_dir(game,
			game->player.pos_x + game->player.size / 2,
			game->player.pos_y + game->player.size / 2,
			0x00FFFF00);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
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
	if (!init_player(game))
		return (__exit(game, INIT_PERSO));
	if (!load_all_textures(game))
		return (__exit(game, INIT_GAME));
	if (!render(game))
		return (__exit(game, RENDERING));
	listen_events(game);
	mlx_loop(game->mlx);
	__exit(game, SUCCESS);
	return (0);
}
