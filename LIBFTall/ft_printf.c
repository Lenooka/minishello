/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:47:56 by otolmach          #+#    #+#             */
/*   Updated: 2024/01/05 17:47:29 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_formats(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_print_c(va_arg(args, int));
	else if (format == 's')
		print_length += ft_print_s(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_print_p(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_print_number(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_print_u(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_x(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += ft_print_percent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			print_length += ft_print_c(str[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}
