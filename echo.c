/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:35:11 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/18 19:31:13 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_flag(char **input)
{
	int		x;

	x = 1;
	while (input[x])
	{
		printf("%s", input[x]);
		x++;
		if (input[x + 1])
			printf(" ");
	}
	printf("\n");
}

void	echo_flag(char **input, int x)
{
	while (input[x])
	{
		printf("%s", input[x]);
		x++;
		if (input[x])
			printf(" ");
	}
}

int check_flag(char *input)
{
	int	x;

	x = 0;
	if (!input)
		return (0);
	if (ft_strlen(input) < 2)
		return (0);
	if (input[x] == '-' && input[x + 1] == 'n')
	{
		x++;
		while (input[x])
		{
			if (input[x] != 'n')
				return (0);
			x++;
		}
		return (1);
	}
	return (0);
}
void	ft_echo(char **inputs)
{
	int	x;
	int	option;

	x = 1;
	option = 0;
	if (inputs[x] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	option = check_flag(inputs[x]);
	x = option;
	while (check_flag(inputs[x]))
		x++;
	if (option)
	{
		echo_flag(inputs, x);
		return ;
	}
	no_flag(inputs);
	return ;
}
