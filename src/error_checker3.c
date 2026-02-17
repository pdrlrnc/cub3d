/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:25:39 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/16 16:25:49 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_line_trim_ptr(t_scene *scene, char *ptr, int fd)
{
	if (!ptr)
	{
		write(STDERR_FILENO, MALLOC_ERR, 37);
		close(fd);
		clean_scene(scene);
		exit(1);
	}
}
