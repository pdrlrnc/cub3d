/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:38:46 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/16 12:14:54 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	next = curr->next;
	while (next != NULL)
	{
		del(curr->content);
		free(curr);
		curr = next;
		next = curr->next;
	}
	del(curr->content);
	free(curr);
	*lst = NULL;
}
