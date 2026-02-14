/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:33:04 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 18:33:09 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_stack_fl_fi(t_scene *scene, t_point *stack, char **map)
{
	if (!stack)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		ft_splitfree(map);
		clean_scene(scene);
		exit(1);
	}
}
