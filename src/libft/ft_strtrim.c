/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:19:17 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/15 19:00:49 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*prototypes*/
static int	ft_trims_front(char const *s1, char const *set);
static int	ft_trims_back(char const *s1, char const *set, int len);
static char	*ft_str_delete(void);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		trims_front;
	int		trims_back;
	char	*result;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	trims_front = ft_trims_front(s1, set);
	if ((size_t)trims_front == ft_strlen(s1))
		return (ft_str_delete());
	trims_back = ft_trims_back(s1, set, ft_strlen(s1) - 1);
	result = malloc(trims_back - trims_front + 2);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (trims_front <= trims_back)
	{
		*(result + i) = *(s1 + trims_front);
		i++;
		trims_front++;
	}
	*(result + i) = '\0';
	return (result);
}

static char	*ft_str_delete(void)
{
	char	*result;

	result = malloc(1);
	if (result == NULL)
		return (NULL);
	*result = '\0';
	return (result);
}

static int	ft_trims_front(char const *s1, char const *set)
{
	int	i;
	int	s;
	int	flag;

	i = 0;
	while (*(s1 + i))
	{
		flag = 0;
		s = 0;
		while (*(set + s))
		{
			if (*(s1 + i) == *(set + s))
			{
				i++;
				flag = 1;
				break ;
			}
			s++;
		}
		if (!flag)
			return (i);
	}
	return (i);
}

static int	ft_trims_back(char const *s1, char const *set, int len)
{
	int	s;
	int	flag;

	while (len >= 0)
	{
		flag = 0;
		s = 0;
		while (*(set + s))
		{
			if (*(s1 + len) == *(set + s))
			{
				len--;
				flag = 1;
				break ;
			}
			s++;
		}
		if (!flag)
			return (len);
	}
	return (len);
}
