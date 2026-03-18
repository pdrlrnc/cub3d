/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:27:16 by pedde-so          #+#    #+#             */
/*   Updated: 2026/03/18 10:27:17 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_if_has_map(t_scene **scene, t_list *list)
{
	if (!(*scene)->is_valid)
		return ;
	while (list && (is_config_line((char *)list->content)
			|| !ft_strcmp((char *)list->content, "\n")))
		list = list->next;
	if (list)
		return ;
	(*scene)->is_valid = 0;
	add_err(scene, MISS_INPUT_8);
}
