/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:00:22 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/15 12:48:10 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)*(s1 + i) != (unsigned char)*(s2 + i))
			return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
		if (*(s1 + i) == '\0')
			return (0);
		i++;
	}
	return (0);
}
/*
int main (void)
{
	char *a = "abcdefgh";
	char *b = "abcdwxyz";

	printf("%d\n", ft_strncmp((const char *)a, (const char *)b, 4));
}*/
