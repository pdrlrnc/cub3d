/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:22:37 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/11 16:23:53 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>*/

/*prototypes*/
static int	ft_number_length(long n);
static char	*ft_negative_itoa(long n);
/*
int	main(void)
{
	char *result;

	result = ft_itoa(42);
	printf("%s\n", result);
	free(result);
	result = ft_itoa(-42);
	printf("%s\n", result);
	free(result);
	result = ft_itoa(INT_MAX);
	printf("%s\n", result);
	free(result);
	result = ft_itoa(INT_MIN);
	printf("%s\n", result);
	free(result);
}
*/

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	long	long_n;

	long_n = n;
	if (long_n < 0)
		return (ft_negative_itoa(-long_n));
	result = malloc(ft_number_length(n) + 1);
	if (result == NULL)
		return (NULL);
	i = ft_number_length(n);
	*(result + i) = '\0';
	i--;
	while (i >= 0)
	{
		*(result + i) = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (result);
}

static int	ft_number_length(long n)
{
	if (n < 10)
		return (1);
	else
		return (1 + ft_number_length(n / 10));
}

static char	*ft_negative_itoa(long n)
{
	char	*result;
	int		i;

	result = malloc(ft_number_length(n) + 2);
	if (result == NULL)
		return (NULL);
	i = ft_number_length(n) + 1;
	*(result + i) = '\0';
	i--;
	while (i > 0)
	{
		*(result + i) = n % 10 + '0';
		n /= 10;
		i--;
	}
	*(result) = '-';
	return (result);
}
