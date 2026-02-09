/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:08:28 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/13 12:54:55 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*prototypes*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (*(dst + i))
		i++;
	if (i >= size)
		return (size + ft_strlen(src));
	k = i;
	j = 0;
	while (*(src + j) && k < size - 1)
	{
		*(dst + k) = *(src + j);
		j++;
		k++;
	}
	j = 0;
	while (*(src + j))
		j++;
	if (k < size)
		*(dst + k) = '\0';
	return (i + j);
}
