/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:56:27 by pedde-so          #+#    #+#             */
/*   Updated: 2025/10/19 12:56:29 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_n(const char *s, size_t n)
{
	size_t	i;
	char	*result;

	if (!s)
		return (NULL);
	result = malloc(n + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(result + i) = *(s + i);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}
