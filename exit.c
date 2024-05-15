/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:45:13 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/15 16:24:09 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_num(int n)
{
	if (n >= 0 && n <= 255)
		return (n);
	else if (n > 255)
	{
		while (n > 255)
			n = n - 256;
	}
	else
	{
		while (n < 0)
			n = n + 256;
	}
	return (n);
}

int	prep_atoi(t_mnshll *ms, char *str)
{
	int	x;

	x = 0;
	if (str[x] == '-' || str[x] == '+')
		x++;
	while (str[x])
	{
		if (str[x] >= '9' || str[x] <= '0')
		{
			error;					//Error handling, message and frees needed.
			return (0);
		}
		x++;
	}
	return (1);
}

void	ft_exit(t_mnshll *mini, char **input)
{
	int	nbr;

	nbr = 0;
	if (input && size_of_2d(input) == 1)
		nbr = 0;
	else if (input[1] && size_of_2d(input) == 2)
	{
		if (prep_atoi(mini, input[1]))
			nbr = ft_atoi(input[1]);
		else
			nbr = 2;
	}
	else if (input[2] && size_of_2d(input) > 2)
	{
		error							//Error handling, message and frees needed.
		nbr = 1;
	}
	nbr = exit_num(nbr);				//leaving it like this for now.
	mini->exit = nbr;
	free_arr(input);
	//ft_printf("exit\n");
	free_ms(mini);
}