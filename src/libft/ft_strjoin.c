/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:53:23 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/16 17:31:06 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*prototypes*/
static char	*ft_strjoin_cont(char const *s1, char const *s2, char *result);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	return (ft_strjoin_cont(s1, s2, result));
}

static char	*ft_strjoin_cont(char const *s1, char const *s2, char *result)
{
	int	i;
	int	s2_iter;

	i = 0;
	while (*(s1 + i))
	{
		*(result + i) = *(s1 + i);
		i++;
	}
	s2_iter = 0;
	while (*(s2 + s2_iter))
	{
		*(result + i) = *(s2 + s2_iter);
		i++;
		s2_iter++;
	}
	*(result + i) = '\0';
	return (result);
}
