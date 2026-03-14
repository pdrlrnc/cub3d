/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:40:55 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:40:57 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	*get_wall_tex(t_game *game, t_ray *r)
{
	if (game->map2d[r->map_y][r->map_x].type == DOOR)
		return (&game->tex_door);
	if (r->side == 0)
	{
		if (r->dir_x > 0)
			return (&game->tex_e);
		return (&game->tex_w);
	}
	if (r->dir_y > 0)
		return (&game->tex_s);
	return (&game->tex_n);
}

int	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		write(STDERR_FILENO, "Error\nError loading texture file\n", 33);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->lsize, &tex->endian);
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->tex_n, game->scene->textures.tex_no))
		return (0);
	if (!load_texture(game, &game->tex_s, game->scene->textures.tex_so))
		return (0);
	if (!load_texture(game, &game->tex_e, game->scene->textures.tex_ea))
		return (0);
	if (!load_texture(game, &game->tex_w, game->scene->textures.tex_we))
		return (0);
	if (!load_texture(game, &game->tex_door, DOOR_TEXT))
		return (0);
	return (1);
}

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->lsize + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_tex_col(t_game *game, int x, t_slice *s, t_tex *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	tex_x = (game->wall_x * tex->width);
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	step = (double)tex->height / s->real_height;
	tex_pos = (s->start - (s->mid_y - s->real_height / 2.0)) * step;
	y = s->start;
	while (y < s->end)
	{
		tex_y = tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		_put_pixel(&game->img, x, y, get_tex_pixel(tex, tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}
