/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:01:47 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/10 19:01:58 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_scene(t_scene *scene)
{
	int	i;

	i = 0;
	printf("[MAP]\n");
	if (scene->map)
	{
		while (scene->map[i])
			printf("%s", scene->map[i]);
		i++;
	}
	printf("\tMAP_W: %d, MAP_H: %d\n", scene->map_w, scene->map_h);
	printf("\tPX: %f, PY: %f\n", scene->px, scene->py);
	printf("\tSPAWN_DIRECTION: ");
	print_direction(scene->spawn_direction);
	printf("\n");
	print_wall_tex(scene->textures);
	printf("\tFLOOR_R[%d]G[%d]B[%d] \t SKY_R[%d]G[%d]B[%d]\n", 
		scene->floor_r, scene->floor_g, scene->floor_b
			,scene->sky_r, scene->sky_g, scene->sky_b);
}

void	print_direction(t_direction direction)
{
	if (direction == NO)
		printf("\tNO\n");
	if (direction == SO)
		printf("\tSO\n");
	if (direction == EA)
		printf("\tEA\n");
	if (direction == WE)
		printf("\tWE\n");
}

void	print_wall_tex(t_wall_tex wall_tex)
{
	if (wall_tex.tex_no)
		printf("Wall texture NORTH: %s\n", wall_tex.tex_no);
	else
		printf("\tTEXT_NO NULL\n");
	if (wall_tex.tex_so)
		printf("Wall texture SOUTH: %s\n", wall_tex.tex_so);
	else
		printf("\tTEXT_SO NULL\n");
	if (wall_tex.tex_ea)
		printf("Wall texture EAST: %s\n", wall_tex.tex_ea);
	else
		printf("\tTEXT_EA NULL\n");
	if (wall_tex.tex_we)
		printf("Wall texture WEST: %s\n", wall_tex.tex_we);
	else
		printf("\tTEXT_WE NULL\n");
}
