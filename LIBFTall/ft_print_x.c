/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xX.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:49:45 by otolmach          #+#    #+#             */
/*   Updated: 2023/10/01 14:49:48 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_dxlen(unsigned int num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static	void	convert_puthex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		convert_puthex(num / 16, format);
		convert_puthex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_print_x(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
	{
		if (num < 0)
		{
			write (1, "-", 1);
			num = -num;
		}
		convert_puthex(num, format);
	}
	return (ft_dxlen(num));
}
