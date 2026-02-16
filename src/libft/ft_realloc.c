/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:56:42 by pedde-so          #+#    #+#             */
/*   Updated: 2025/09/24 17:56:45 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_realloc_cont(void *ptr, void *res, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	dst = (unsigned char *)res;
	src = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	return (res);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*res;

	if (!ptr && new_size)
		return (malloc(new_size));
	if (!ptr)
		return (NULL);
	if (ptr && !new_size)
		return (free(ptr), NULL);
	res = malloc(new_size);
	if (!res)
		return (NULL);
	if (old_size < new_size)
		return (ft_realloc_cont(ptr, res, old_size));
	else
		return (ft_realloc_cont(ptr, res, new_size));
}
