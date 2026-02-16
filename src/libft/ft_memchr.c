/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:27:42 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/15 13:08:03 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	c_char;

	ptr = (unsigned char *)s;
	c_char = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*(ptr + i) == c_char)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
/*
int main (void)
{
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	printf("%s", (char *)ft_memchr(tab, -1, 7));
}*/
