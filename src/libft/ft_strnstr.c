/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:00:34 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/13 09:59:31 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;
	size_t	c;

	if (*(little) == '\0')
		return ((char *)(big));
	b = 0;
	while (*(big + b) && b < len)
	{
		l = 0;
		if (*(big + b) == *(little + l))
		{
			c = b;
			while (*(big + c) == *(little + l) && *(little + l) && c < len)
			{
				c++;
				l++;
			}
			if (*(little + l) == '\0')
				return ((char *)(big + b));
		}
		b++;
	}
	return (NULL);
}
