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

//function used in every malloc, if there is not a pointer to free, you should
//set the param as NULL and if there is no fd to close, set it at -1. be mindful
//of the use of this function, if there is an error the program will terminate,
//so please free everything you need before
void	check_malloc(void *ptr, void *to_free, int fd)
{
	if (!ptr)
	{
		write(STDERR_FILENO, "Unknown error with malloc\n", 26);
		if (fd > 0)
			close(fd);
		free(to_free);
		exit(1);
	}
}

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
