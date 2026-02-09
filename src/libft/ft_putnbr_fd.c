/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:01:03 by pedde-so          #+#    #+#             */
/*   Updated: 2025/04/15 18:53:56 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*prototypes*/
static void	ft_putnbr_fd_long(long n, int fd);

void	ft_putnbr_fd(long n, int fd)
{
	ft_putnbr_fd_long(n, fd);
}

static void	ft_putnbr_fd_long(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd_long(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}
