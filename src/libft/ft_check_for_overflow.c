/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_for_overflow.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:12:43 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/04 16:12:46 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_for_overflow(char *nb)
{
	char	*max_int;
	int		i;

	max_int = "2147483647";
	if (ft_strlen(nb) > 10)
		return (1);
	if (ft_strlen(nb) < 10)
		return (0);
	i = 0;
	while (*(nb + i))
	{
		if (*(nb + i) > *(max_int + i))
			return (1);
		i++;
	}
	return (0);
}
