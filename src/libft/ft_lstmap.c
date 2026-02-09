/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:49:10 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/16 12:03:07 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*prototypes*/
static t_list	*ft_cleanup(t_list *lst, t_list *new_node, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*dummy;
	t_list	*new_node;	

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	result = NULL;
	dummy = NULL;
	while (lst != NULL)
	{
		new_node = malloc(sizeof(t_list));
		if (new_node == NULL)
			return (ft_cleanup(result, NULL, del));
		new_node->content = f(lst->content);
		if (new_node->content == NULL)
			return (ft_cleanup(result, new_node, del));
		new_node->next = NULL;
		if (result == NULL)
			result = new_node;
		else
			dummy->next = new_node;
		dummy = new_node;
		lst = lst->next;
	}
	return (result);
}

static t_list	*ft_cleanup(t_list *lst, t_list *new_node, void (*del)(void *))
{
	t_list	*next;

	if (new_node != NULL)
		free(new_node);
	while (lst != NULL)
	{
		next = lst->next;
		if (lst->content != NULL)
			del(lst->content);
		free(lst);
		lst = next;
	}
	return (NULL);
}
