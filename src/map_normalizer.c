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

char	**normalize_map(t_scene **scene)
{
	char	**normalized_map;
	int	i;
	int	j;
	int	k;
	int	l;

	normalized_map = malloc(sizeof(char *) * ((*scene)->map_h + 3));
	i = 0;
	l = 0;
	while (i < ((*scene)->map_h + 2))
	{
		normalized_map[i] = malloc(sizeof(char) * ((*scene)->map_w + 3));
		j = 0;
		if (i == 0 || i == ((*scene)->map_h + 1))
		{
			while (j < ((*scene)->map_w + 2))
				normalized_map[i][j++] = 'V';
		}
		else
		{
			normalized_map[i][j++] = 'V';
			k = 0;
			while (k < (*scene)->map_w)
			{
				if ((*scene)->map[l][k] == ' ')
					normalized_map[i][j] = 'V';
				else
					normalized_map[i][j] = (*scene)->map[l][k];
				j++;
				k++;
			}
			l++;
			normalized_map[i][j++] = 'V';
		}
		normalized_map[i][j] = '\0';
		i++;
	}
	normalized_map[i] = NULL;
	return (normalized_map);
}
