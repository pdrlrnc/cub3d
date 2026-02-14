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

t_point	*create_stack(int x, int y, int width, int height)
{
	t_point	dummy;
	t_point	*res;
	t_point	first;
	int		i;

	res = malloc(sizeof(t_point) * ((width * height) + 1));
	if (!res)
		return (NULL);
	i = 0;
	first.x = x;
	first.y = y;
	first.top = 0;
	dummy.top = 1;
	res[0] = dummy;
	res[1] = first;
	return (res);
}

t_point	pop(t_point *stack, int top)
{
	t_point	res;

	res = stack[top];
	stack->top = top - 1;
	return (res);
}

int	push(t_point *stack, int top, int x, int y)
{
	t_point	to_push;

	to_push.x = x;
	to_push.y = y;
	top++;
	to_push.top = top;
	stack[top] = to_push;
	stack->top = top;
	return (top);
}
