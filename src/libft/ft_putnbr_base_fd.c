/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:44:14 by pedde-so          #+#    #+#             */
/*   Updated: 2025/05/17 14:12:40 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
   int main(void)
   {
   ft_putnbr_base(42, "0123456789");       // Decimal: 42
   write(1, "\n", 1);
   ft_putnbr_base(-12, "01");                // Binário: 101010
   write(1, "\n", 1);
   ft_putnbr_base(42, "0123456789ABCDEF");  // Hexadecimal: 2A
   write(1, "\n", 1);
   ft_putnbr_base(42, "poneyvif");          // Base 8 personalizada: "v"
   write(1, "\n", 1);
   ft_putnbr_base(-42, "0123456789");       // Número negativo em decimal: -42
   write(1, "\n", 1);
   ft_putnbr_base(-42, "01");     // Número negativo em binário: -101010
   write(1, "\n", 1);
   ft_putnbr_base(0, "0123456789");         // Zero em decimal: 0
   write(1, "\n", 1);

// Testes de erro
ft_putnbr_base(42, "");                  // Base vazia
ft_putnbr_base(42, "1");                 // Base com um único caractere
ft_putnbr_base(42, "01234+6789");        // Base com caractere inválido '+'
ft_putnbr_base(42, "01234456789");       // Base com caractere repetido

return 0;
}
*/

static int	ft_is_valid_base(char *base, int base_len)
{
	int	i;
	int	k;

	if (base_len < 2)
		return (0);
	i = 0;
	while (*(base + i))
	{
		if (*(base + i) == '+' || *(base + i) == '-')
			return (0);
		k = i + 1;
		while (*(base + k))
		{
			if (*(base + i) == (*(base + k)))
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

static void	ft_fill_array(char *ptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		*(ptr + i) = '\0';
		i++;
	}
}

static int	ft_print(unsigned long long nb, int base, char *characters, int fd)
{
	int			i;
	char		number[64];
	int			count;

	count = 0;
	ft_fill_array(number, 64);
	i = 63;
	while (nb > 0)
	{
		number[i--] = characters[(nb % base)];
		nb /= base;
		count++;
	}
	if (fd != -1)
		write(fd, &number[i + 1], count);
	return (count);
}

int	ft_putnbr_base_fd(unsigned long long nbr, char *base, int fd)
{
	int	base_len;

	if (nbr == 0 && fd != -1)
	{
		write(fd, &base[0], 1);
		return (1);
	}
	if (nbr == 0 && fd == -1)
		return (1);
	base_len = 0;
	while (*(base + base_len))
		base_len++;
	if (!ft_is_valid_base(base, base_len))
		return (0);
	return (ft_print((unsigned long long) nbr, base_len, base, fd));
}
