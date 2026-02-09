/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:10:36 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/16 17:32:26 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*prototypes*/
static char	*ft_invalid_input(void);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*result;
	size_t	i;

	if (s == NULL)
		return (ft_invalid_input());
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_invalid_input());
	if (s_len - start < len)
		len = s_len - start;
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(result + i) = *(s + start);
		i++;
		start++;
	}
	*(result + i) = '\0';
	return (result);
}

static char	*ft_invalid_input(void)
{
	char	*result;

	result = malloc(1);
	if (result == NULL)
		return (NULL);
	*result = '\0';
	return (result);
}
