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

void	check_norm_ptr(t_scene *scene, char **map, char *ptr, int i)
{
	if (!ptr)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		ft_splitfree_error(map, i);
		clean_scene(scene);
		exit(1);
	}
}

void	add_err(t_scene **scene, char *err_mess)
{
	int	i;

	(*scene)->is_valid = 0;
	i = 0;
	while ((*scene)->err_mess[i])
		i++;
	(*scene)->err_mess[i] = err_mess;
}

void	print_err(t_scene *scene)
{
	int	i;

	write(STDERR_FILENO, "Error\n", 6);
	i = 0;
	while (scene->err_mess[i])
	{
		ft_putstr_fd(scene->err_mess[i], STDERR_FILENO);
		i++;
	}
}

void	check_colour_trim_ptr(t_scene *scene, char **res, char **rgb, char **og_split)
{
	if (!res)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		ft_splitfree(rgb);
		ft_splitfree(og_split);
		clean_scene(scene);
		exit(1);
	}
}
