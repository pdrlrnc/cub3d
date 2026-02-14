/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 18:06:55 by pedde-so          #+#    #+#             */
/*   Updated: 2026/02/12 18:06:55 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	stack_is_empty(t_point	*stack)
{
	return (stack == NULL);
}

t_point	*create_stack(int x, int y, int width, int height)
{
	t_point	*res;
	t_point	first;
	int		i;

	res = malloc(sizeof(t_point) * (width * height));
	if (!res)
		return (NULL);
	i = 0;
	first.x = x;
	first.y = y;
	res[0] = first;
	return (res);
}

t_point	pop(t_point *stack, int top)
{
	t_point	res;

	res = stack[top];
	return (res);
}

int	push(t_point *stack, int top, int x, int y)
{
	t_point	to_push;

	to_push.x = x;
	to_push.y = y;
	stack[++top] = to_push;
	return (top);
}
