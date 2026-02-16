/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:07:55 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/15 18:08:16 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	last;
	int	i;

	c = c % 256;
	last = -1;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			last = i;
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	if (last != -1)
		return ((char *)(s + last));
	return (NULL);
}
