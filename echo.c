/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:35:11 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/26 03:11:15 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_flag(char **input) //Do we reeeeallly need ft_printf? We shall see.
{
	int		x;
	char	*str;

	x = 1;
	while (input[x])
	{
		str = ft_strdup(input[x]);
		if (!str)
		{
			printf("%s", input[x]);
			if (input[x + 1])
				printf(" ");
		}
		else
		{
			printf("%s", str);
			if (input[x + 1])
				printf(" ");
			free(str);
		}
		x++;
	}
	printf("\n");
}

void	echo_flag(char **input, int x)
{
	char	*str;

	while (input[x])
	{
		str = ft_strdup(input[x]);
		if (!str)
			printf("%s", input[x]);
		else
		{
			printf("%s", str);
			free(str);
		}
		if (cmd_line[x + 1])
			ft_printf(" ");
		x++;
	}
}

int	check_flag(char *input) //Should work, might be trolling doe, who knows? Cluegi.
{
	int	x;
	
	x = 0;
	if (!input)
		return (0);
	if (input[x] == '-')
	{
		x++;
		while (input[x] == 'n')
			x++;
	}
	if (x < 2)
		return (0);
	if (!input[x])
		return (1);
	return (0);
}

void	echo(char **inputs)
{
	int	x;
	int	option;

	x = 1;
	option = 0;
	if (!inputs[i])
	{
		printf("\n");
		return ;
	}
	while (check_flag(inputs[x]))
	{
		option++;
		x++;
	}
	if (option)
		echo_flag(inputs, x);
	else
		no_flag(inputs);
}