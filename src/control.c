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
	if (keycode == ON_ESC)
		__exit(game, SUCCESS);
	if (keycode == ON_LEFT)
		game->keys.left = 1;
	if (keycode == ON_A)
		game->keys.mleft = 1;
	if (keycode == ON_W)
		game->keys.up = 1;
	if (keycode == ON_RIGHT)
		game->keys.right = 1;
	if (keycode == ON_D)
		game->keys.mright = 1;
	if (keycode == ON_S)
		game->keys.down = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == ON_LEFT)
		game->keys.left = 0;
	if (keycode == ON_A)
		game->keys.mleft = 0;
	if (keycode == ON_W)
		game->keys.up = 0;
	if (keycode == ON_RIGHT)
		game->keys.right = 0;
	if (keycode == ON_D)
		game->keys.mright = 0;
	if (keycode == ON_S)
		game->keys.down = 0;
	if (keycode == ON_M)
		game->minimap_active = _switch(game->minimap_active);
	if (keycode == ON_F)
		game->fisheye = _switch(game->fisheye);
	if (keycode == ON_E)
		try_teleport(game);
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

	speed = game->grid_size * 0.05;
	rad = define_angle(game);
	move_up_down(game, rad, speed);
	move_right_left(game, rad, speed);
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
