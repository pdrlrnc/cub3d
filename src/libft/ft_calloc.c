/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:43:36 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/16 12:42:29 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			len;
	size_t			i;
	void			*result;
	unsigned char	*zeroed_result;

	len = nmemb * size;
	if (size && (len / size != nmemb))
		return (NULL);
	result = malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	zeroed_result = result;
	i = 0;
	while (i < len)
	{
		*(zeroed_result + i) = '\0';
		i++;
	}
	return (result);
}
