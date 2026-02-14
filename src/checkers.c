/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:22:24 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 18:22:30 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_validity(t_scene **scene)
{
	if (!(*scene)->textures.has_no || !(*scene)->textures.has_so
		|| !(*scene)->textures.has_ea || !(*scene)->textures.has_we)
		(*scene)->is_valid = 0;
	if ((*scene)->floor_r == -1 || (*scene)->floor_g == -1
		|| (*scene)->floor_b == -1)
		(*scene)->is_valid = 0;
	if ((*scene)->sky_r == -1 || (*scene)->sky_g == -1 || (*scene)->sky_b == -1)
		(*scene)->is_valid = 0;
}
