/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shrink_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:04:08 by pedde-so          #+#    #+#             */
/*   Updated: 2025/08/09 11:04:09 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**prototypes**/
static char	**cont(char **split, char **new_split, int first, int last);
static void	not_first(char **new_split, char **split, int *i, int *j);

char	**ft_shrink_split(char **split, int first, int last)
{
	char	**new_split;
	int		i;

	if (!split || !split[0])
		return (NULL);
	if (first >= last)
		return (split);
	i = 0;
	while (split[i])
		i++;
	new_split = malloc((1 + i - (last - first)) * sizeof(char *));
	if (!new_split)
		return (split);
	new_split = cont(split, new_split, first, last);
	ft_splitfree(split);
	return (new_split);
}

static char	**cont(char **split, char **new_split, int first, int last)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (i == first)
		{
			new_split[j] = ft_strdup(split[i]);
			if (!new_split[j])
				return (ft_splitfree_error(split, --j));
			while (++i <= last)
			{
				new_split[j] = ft_strdup_append(NULL, new_split[j], split[i]);
				if (!new_split[j])
					return (ft_splitfree_error(split, --j));
				j++;
			}
		}
		else
			not_first(new_split, split, &i, &j);
	}
	new_split[j] = NULL;
	return (new_split);
}

static void	not_first(char **new_split, char **split, int *i, int *j)
{
	new_split[(*j)++] = ft_strdup(split[(*i)++]);
	if (!new_split[*j - 1])
		(ft_splitfree_error(split, --(*j)));
}
