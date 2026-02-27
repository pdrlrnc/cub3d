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
	{
		free(game->map2d[y]);
		y++;
	}
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
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
	return (0);
}

int	__exit(t_game *game, e_excode code)
{
	if (code > 0)
		return (write(STDOUT_FILENO, "Error\n", 6), code);
	else
		return (_clean(game), code);
}
