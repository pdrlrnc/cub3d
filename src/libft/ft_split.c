/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:55:02 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/27 14:46:58 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/*prototypes*/
static int	ft_count_words(char const *s, char c);
static char	*ft_get_word(char const *s, char c, int index);
static char	*ft_found_word(char const *s, int i, int j);
static char	**ft_cleanup(char **result, int i);

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	int		i;

	if (s == NULL)
		return (NULL);
	c = c % 256;
	words = ft_count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = ft_get_word(s, c, i);
		if (result[i] == NULL)
			return (ft_cleanup(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}

static char	**ft_cleanup(char **result, int i)
{
	i--;
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (NULL);
}

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		if (*(s + i))
			count++;
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (count);
}

static char	*ft_get_word(char const *s, char c, int index)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		if (*(s + i))
		{
			count++;
			if (count == (index + 1))
			{
				j = i;
				while (*(s + j) && *(s + j) != c)
					j++;
				return (ft_found_word(s, i, j));
			}
		}
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (NULL);
}

static char	*ft_found_word(char const *s, int i, int j)
{
	char	*result;
	int		r;

	result = malloc(j - i + 1);
	if (result == NULL)
		return (NULL);
	r = 0;
	while (i < j)
	{
		*(result + r) = *(s + i);
		i++;
		r++;
	}
	*(result + r) = '\0';
	return (result);
}
