/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:58:00 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/06 17:58:02 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			mc;
	long			g;

	i = 0;
	g = 0;
	mc = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mc *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		g = g * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(g * mc));
}
