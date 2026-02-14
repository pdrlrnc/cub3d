/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitfree_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:55:30 by pedde-so          #+#    #+#             */
/*   Updated: 2025/11/12 15:05:26 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitfree_error(char **split, int i)
{
	while (i)
	{
		free(split[i]);
		i--;
	}
	free(split);
	return (NULL);
}
