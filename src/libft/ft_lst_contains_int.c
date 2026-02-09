/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_contains_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:35:57 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/20 12:35:59 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_contains_int(t_list *lst, int *content)
{
	while (lst)
	{
		if (*(int *)lst->content == *(int *)content)
			return (1);
		lst = lst->next;
	}
	return (0);
}
