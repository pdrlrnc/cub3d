/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vibarre <vibarre@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:41:28 by vibarre           #+#    #+#             */
/*   Updated: 2026/02/23 16:41:29 by vibarre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max(int x1, int x2)
{
	if (x1 > x2)
		return (x1);
	return (x2);
}

int	in(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}
