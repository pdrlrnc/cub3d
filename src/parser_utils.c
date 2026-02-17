/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:47:12 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 19:47:20 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_bzeroed_scene_cont(t_scene *scene)
{
	scene->map_w = -1;
	scene->map_h = -1;
	scene->px = -1;
	scene->py = -1;
	scene->spawn_direction = ERR;
	scene->textures.tex_no = NULL;
	scene->textures.tex_so = NULL;
	scene->textures.tex_we = NULL;
	scene->textures.tex_ea = NULL;
	scene->textures.has_no = 0;
	scene->textures.has_so = 0;
	scene->textures.has_we = 0;
	scene->textures.has_ea = 0;
	scene->floor_r = -1;
	scene->floor_g = -1;
	scene->floor_b = -1;
	scene->sky_r = -1;
	scene->sky_g = -1;
	scene->sky_b = -1;
	scene->is_valid = 1;
}

t_scene	*get_bzeroed_scene(void)
{
	t_scene	*scene;
	int		i;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		(write(STDERR_FILENO, MALLOC_ERR, 37), exit(1));
	scene->err_mess = malloc(sizeof(char *) * 12);
	if (!scene->err_mess)
		(free(scene), write(STDERR_FILENO, MALLOC_ERR, 37), exit(1));
	i = 0;
	while (i < 12)
	{
		scene->err_mess[i] = NULL;
		i++;
	}
	scene->map = NULL;
	scene->input_list = NULL;
	get_bzeroed_scene_cont(scene);
	return (scene);
}

void	clean_scene(t_scene *scene)
{
	ft_lstclear(&(scene->input_list), free);
	ft_splitfree(scene->map);
	free(scene->err_mess);
	free(scene->textures.tex_no);
	free(scene->textures.tex_so);
	free(scene->textures.tex_we);
	free(scene->textures.tex_ea);
	free(scene);
}

char	**trim_colours(t_scene **scene, char **rgb, char **original_split)
{
	char	**res;

	if (ft_splitlen(rgb) != 3)
		return (rgb);
	res = malloc(sizeof(char *) * 4);
	check_colour_trim_ptr(*scene, res, rgb, original_split);
	res[0] = ft_strtrim(rgb[0], " ");
	if (!res[0])
		(ft_splitfree_error(rgb, 0), check_colour_trim_ptr(*scene,
				NULL, rgb, original_split));
	res[1] = ft_strtrim(rgb[1], " ");
	if (!res[1])
	{
		ft_splitfree_error(rgb, 1);
		check_colour_trim_ptr(*scene, NULL, rgb, original_split);
	}
	res[2] = ft_strtrim(rgb[2], " ");
	if (!res[2])
	{
		ft_splitfree_error(rgb, 2);
		check_colour_trim_ptr(*scene, NULL, rgb, original_split);
	}
	res[3] = NULL;
	ft_splitfree(rgb);
	return (res);
}

char	*trim_line(t_scene **scene, char *line, int fd)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(line) + 1 + 2));
	check_line_trim_ptr(*scene, res, fd);
	i = 0;
	j = 0;
	while (*(line + i) && *(line + i) == ' ')
		i++;
	*(res + j++) = *(line + i++);
	if (is_texture_line(line))
		*(res + j++) = *(line + i++);
	*(res + j++) = ' ';
	while (*(line + i))
	{
		if (is_texture_line(line) || *(line + i) != ' ')
			*(res + j++) = *(line + i);
		i++;
	}
	*(res + j) = '\0';
	free(line);
	return (res);
}
