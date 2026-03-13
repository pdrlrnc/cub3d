/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:56:25 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:56:26 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	_clean(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->scene->map_h)
		free(game->map2d[y++]);
	free(game->map2d);
	clean_scene(game->scene);
	if (game->tex_n.img)
		mlx_destroy_image(game->mlx, game->tex_n.img);
	if (game->tex_s.img)
		mlx_destroy_image(game->mlx, game->tex_s.img);
	if (game->tex_e.img)
		mlx_destroy_image(game->mlx, game->tex_e.img);
	if (game->tex_w.img)
		mlx_destroy_image(game->mlx, game->tex_w.img);
	if (game->tex_door.img)
		mlx_destroy_image(game->mlx, game->tex_door.img);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
	return (0);
}

static int	_clean_init_game(t_game *game)
{
	clean_scene(game->scene);
	if (!game->mlx)
		write(STDERR_FILENO, "Error\nAlloc error in mlx_init\n", 30);
	else if (!game->mlx_win)
		write(STDERR_FILENO, "Error\nAlloc error in mlx_new_window\n", 37);
	else if (!game->img.img)
		write(STDERR_FILENO, "Error\nAlloc error in mlx_new_image\n", 35);
	else
		write(STDERR_FILENO, "Error\nAlloc error in mlx_get_data_addr\n", 39);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(ALLOCATION);
	return (ALLOCATION);
}

static int	_clean_init_map2d(t_game *game)
{
	int	y;

	write(STDERR_FILENO, "Error\nAlloc error initiating 2d map\n", 36);
	if (game->map2d)
	{
		y = 0;
		while (game->map2d[y])
			free(game->map2d[y++]);
		free(game->map2d);
	}
	clean_scene(game->scene);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(ALLOCATION);
	return (ALLOCATION);
}

int	__exit(t_game *game, t_excode_enum code)
{
	if (!game->scene)
		return (free(game), code);
	else if (code == INIT_GAME)
		return (_clean_init_game(game));
	else if (code == INIT_MAP2D)
		return (_clean_init_map2d(game));
	else
		return (_clean(game), code);
}
