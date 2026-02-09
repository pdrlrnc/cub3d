/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:49:24 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/16 17:39:14 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>
/*prototypes*/
static void	*ft_bckwrds_cpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	if (dest == src || n == 0)
		return (dest);
	if (dest > src)
		return (ft_bckwrds_cpy(dest, src, n));
	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(ptr_dest + i) = *(ptr_src + i);
		i++;
	}
	return (dest);
}

static void	*ft_bckwrds_cpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = n - 1;
	while (i > 0)
	{
		*(ptr_dest + i) = *(ptr_src + i);
		i--;
	}
	*(ptr_dest) = *(ptr_src);
	return (dest);
}
/*
int main (void)
{
 	char *src = "thanks to @apellicc for this test !\r\n";
 	char dst1[0xF0];
 	int size = strlen(src);
 	char *r1 = memmove(dst1, src, size);
 	char *r2 = ft_memmove(dst1, src, size);
 
 	if (r1 != r2)
		printf("foda-se\n");
 	r1 = memmove("", "" - 1, 0);
 	r2 = ft_memmove("", "" - 1, 0);
 	if (r1 != r2)
		printf("foda-se\n"); 
}
*/
