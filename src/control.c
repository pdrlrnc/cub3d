/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:41:04 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:41:06 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_game *game)
{
	printf("keycode=%d\n", keycode);
	if (keycode == ON_ESC)
		__exit(game, SUCCESS);
	if (keycode == ON_LEFT)
		game->keys.left = 1;
	if (keycode == ON_UP)
		game->keys.up = 1;
	if (keycode == ON_RIGHT)
		game->keys.right = 1;
	if (keycode == ON_DOWN)
		game->keys.down = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == ON_LEFT)
		game->keys.left = 0;
	if (keycode == ON_UP)
		game->keys.up = 0;
	if (keycode == ON_RIGHT)
		game->keys.right = 0;
	if (keycode == ON_DOWN)
		game->keys.down = 0;
	if (keycode == ON_M)
	{
		if (game->minimap_active == 1)
			game->minimap_active = 0;
		else
			game->minimap_active = 1;
	}
	if (keycode == ON_F)
	{
		if (game->fisheye == 1)
			game->fisheye = 0;
		else
			game->fisheye = 1;
	}
	return (0);
}

static double	define_angle(t_game *game)
{
	double	rad;

	if (game->keys.left)
		game->player.angle -= ANGLE_SPEED;
	if (game->keys.right)
		game->player.angle += ANGLE_SPEED;
	game->player.angle = normalize_angle(game->player.angle);
	rad = game->player.angle * M_PI / 180;
	return (rad);
}

int	game_loop(t_game *game)
{
	double	rad;
	double	speed;
	double	move_x;
	double	move_y;

	speed = game->grid_size * 0.02;
	rad = define_angle(game);
	move_x = cos(rad) * speed;
	move_y = sin(rad) * speed;
	if (game->keys.up)
	{
		if (can_move(game, game->player.pos_x + move_x, game->player.pos_y))
			game->player.pos_x += move_x;
		if (can_move(game, game->player.pos_x, game->player.pos_y + move_y))
			game->player.pos_y += move_y;
	}
	if (game->keys.down)
	{
		if (can_move(game, game->player.pos_x - move_x, game->player.pos_y))
			game->player.pos_x -= move_x;
		if (can_move(game, game->player.pos_x, game->player.pos_y - move_y))
			game->player.pos_y -= move_y;
	}
	render(game);
	return (1);
}

void	listen_events(t_game *game)
{
	mlx_hook(game->mlx_win, ON_KEYPRESS, 1L << 0, key_press, game);
	mlx_hook(game->mlx_win, ON_KEYRELEASE, 1L << 1, key_release, game);
	mlx_hook(game->mlx_win, ON_DESTROY, 0, _clean, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
