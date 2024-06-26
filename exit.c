/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:45:13 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/23 15:40:22 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(t_mnshll *mini, int x)
{
	if (x == 1)
		error_msg(mini, "too many arguments : ", 1, "exit");
	if (x == 2)
		error_msg(mini, "Error: numeric argument required : ", 1, "exit");
	return (x);
}

int	exit_num(int number)
{
	if (number >= 0 && number <= 255)
		return (number);
	if (number > 255)
		return (exit_num(number - 256));
	if (number < 0)
		return (exit_num(number + 256));
	return (number);
}

int	prep_atoi(char *str)
{
	int	x;

	x = 0;
	if (str[x] == '-' || str[x] == '+')
		x++;
	while (str[x])
	{
		if (str[x] > '9' || str[x] < '0')
			return (0);
		x++;
	}
	return (1);
}

void	ft_exit(t_mnshll *mini, char **input)
{
	int	number;

	number = 0;
	if (!input[1])
		;
	else if (input[1] && !input[2])
	{
		if (prep_atoi(input[1]))
			number = ft_atoi(input[1]);
		else
			number = exit_error(mini, 2);
	}
	else
		number = exit_error(mini, 1);
	number = exit_num(number);
	mini->exit = number;
	free_all_arrays(input);
	close_fd(mini->pipefd);
	printf("exit\n");
	free_exit_procces(mini, NULL);
}
