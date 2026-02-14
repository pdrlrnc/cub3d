/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:20:23 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 16:20:29 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	normalize_map_cont(t_scene **scene,
			t_norm_indexes *ind, char **normalized_map)
{
	normalized_map[ind->i][ind->j++] = 'V';
	ind->k = 0;
	while (ind->k < (*scene)->map_w)
	{
		if ((*scene)->map[ind->l][ind->k] == ' ')
			normalized_map[ind->i][ind->j] = 'V';
		else
			normalized_map[ind->i][ind->j] = (*scene)->map[ind->l][ind->k];
		ind->j++;
		ind->k++;
	}
	ind->l++;
	normalized_map[ind->i][ind->j++] = 'V';
}

char	**normalize_map(t_scene **scene)
{
	char			**normalized_map;
	t_norm_indexes	ind;

	normalized_map = malloc(sizeof(char *) * ((*scene)->map_h + 3));
	check_double_ptr(*scene, normalized_map);
	ind.i = 0;
	ind.l = 0;
	while (ind.i < ((*scene)->map_h + 2))
	{
		normalized_map[ind.i] = malloc(sizeof(char) * ((*scene)->map_w + 3));
		check_norm_ptr(*scene, normalized_map, normalized_map[ind.i], ind.i);
		ind.j = 0;
		if (ind.i == 0 || ind.i == ((*scene)->map_h + 1))
		{
			while (ind.j < ((*scene)->map_w + 2))
				normalized_map[ind.i][ind.j++] = 'V';
		}
		else
			normalize_map_cont(scene, &ind, normalized_map);
		normalized_map[ind.i][ind.j] = '\0';
		ind.i++;
	}
	normalized_map[ind.i] = NULL;
	return (normalized_map);
}
