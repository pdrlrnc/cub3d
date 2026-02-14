/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:21:35 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/14 18:21:44 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run_flood_fill(t_scene **scene, char **map)
{
	t_point	*stack;
	t_point	curr;

	stack = create_stack(0, 0, (*scene)->map_w + 2, (*scene)->map_h + 2);
	check_stack_fl_fi(*scene, stack, map);
	while (stack->top > 0)
	{
		curr = pop(stack, stack->top);
		if (is_walkable(map[curr.x][curr.y]))
			return (free(stack), 0);
		if (map[curr.x][curr.y] == 'V')
			found_v(scene, stack, map, curr);
	}
	free(stack);
	return (1);
}

void	found_v(t_scene **scene, t_point *stack, char **map, t_point curr)
{
	map[curr.x][curr.y] = '*';
	if ((curr.x + 1) < ((*scene)->map_h + 2) && map[curr.x + 1][curr.y] != '*')
		push(stack, stack->top, curr.x + 1, curr.y);
	if ((curr.y + 1) < ((*scene)->map_w + 2) && map[curr.x][curr.y + 1] != '*')
		push(stack, stack->top, curr.x, curr.y + 1);
	if ((curr.x - 1) >= 0 && map[curr.x - 1][curr.y] != '*')
		push(stack, stack->top, curr.x - 1, curr.y);
	if ((curr.y - 1) >= 0 && map[curr.x][curr.y - 1] != '*')
		push(stack, stack->top, curr.x, curr.y - 1);
}
