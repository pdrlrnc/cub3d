/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:34:54 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/09 14:35:05 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_colour_double_ptr(t_scene *scene, char **ptr, char **old_split)
{
	if (!ptr)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		ft_splitfree(old_split);
		clean_scene(scene);
		exit(1);
	}
}

void	check_double_ptr(t_scene *scene, char **ptr)
{
	if (!ptr)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		clean_scene(scene);
		exit(1);
	}
}

void	check_texture_ptr(t_scene *scene, char *ptr, char **split)
{
	if (!ptr)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		ft_splitfree(split);
		clean_scene(scene);
		exit(1);
	}
}

void	check_inp_vals_ptr(t_scene *scene, t_list *list, int fd)
{
	if (!list)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		close(fd);	
		clean_scene(scene);
		exit(1);
	}
}
