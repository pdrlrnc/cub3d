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
	scene->textures.has_so = -1;
	scene->textures.has_we = -1;
	scene->textures.has_ea = -1;
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

	scene = malloc(sizeof(t_scene));
	scene->map = NULL;
	scene->input_list = NULL;
	scene->map_w = -1;
	scene->map_h = -1;
	scene->px = -1;
	scene->py = -1;
	scene->spawn_direction = ERR;
	scene->textures.tex_no = NULL;
	scene->textures.tex_so = NULL;
	scene->textures.tex_we = NULL;
	scene->textures.tex_ea = NULL;
	scene->textures.has_no = -1;
	get_bzeroed_scene_cont(scene);
	return (scene);
}

void	clean_scene(t_scene *scene)
{
	ft_lstclear(&(scene->input_list), free);
	ft_splitfree(scene->map);
	free(scene->textures.tex_no);
	free(scene->textures.tex_so);
	free(scene->textures.tex_we);
	free(scene->textures.tex_ea);
	free(scene);
}
