/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:06:39 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/24 19:10:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_lexer *cmdlist)
{
	t_lexer	*tmp;
	t_lexer	*head;

	head = cmdlist;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->tokens)
			free(tmp->tokens);
		free(tmp);
	}
}


void	free_exit_procces(t_mnshll *minsh, char *mess)
{
	int	exit_s;

	exit_s = minsh->exit;
	if (minsh->input)
		free(minsh->input);
	if (minsh->com_array)
		free_all_arrays(minsh->com_array);
	if (minsh->envl)
		free_env(minsh->envl);
	if (minsh->list_com)
		free_cmd_list(minsh->list_com);
	close(stdin);
	close(stdout);
	close(stderr);
	if (minsh->fdin != -1)
		close(minsh->fdin);
	if (minsh->fdout != -1)
		close(minsh->fdout);
	if (minsh)
		free(minsh);
	rl_clear_history();
	printf("%s\n", mess);
	exit(exit_s);			
}
