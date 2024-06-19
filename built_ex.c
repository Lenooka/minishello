/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:14:21 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/19 18:59:54 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_ex(t_mnshll *minsh, char **tokens)
{
	minsh->exit = 0;
	tokens = rem_q_from_2d(tokens);
	if (ft_strcmp(tokens[0], "echo") == 0)
		ft_echo(tokens);
	else if (ft_strcmp(tokens[0], "cd") == 0)
		cd(minsh, tokens);
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(tokens[0], "export") == 0)
		ft_export(minsh, tokens);
	else if (ft_strcmp(tokens[0], "unset") == 0)
		unset(minsh, tokens);
	else if (ft_strcmp(tokens[0], "env") == 0)
		env(minsh);
	else if (ft_strcmp(tokens[0], "exit") == 0)
		ft_exit(minsh, tokens);
	free_all_arrays(tokens);
}
