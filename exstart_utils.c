/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exstart_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:18:04 by olena             #+#    #+#             */
/*   Updated: 2024/06/24 15:33:16 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal(void)
{
	signal(SIGPIPE, signal_global);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

int	find_com_pos(char **arr, int pos)
{
	int	i;

	i = pos;
	while (arr[i] && arr[i][0] && ft_strcmp(arr[i], "|" ) != 0)
		i++;
	if (arr[i] && arr[i][0] && ft_strcmp(arr[i], "|" ) == 0)
		i++;
	return (i);
}


char	**convert_env(t_envl **envlist)
{
	int		indx;
	int		list_len;
	char	**env;
	char	*indetef;
	t_envl	*tmp;

	indx = 0;
	tmp = *envlist;
	list_len = ft_lstsize(tmp);
	env = malloc(sizeof(char *) * (list_len + 1));
	if (!env)
		return (NULL);
	while (tmp && indx < list_len)
	{
		indetef = ft_strjoin(tmp->identificator, "=");
		env[indx] = ft_strjoin(indetef, tmp->content);
		tmp = tmp->next;
		free(indetef);
		indx++;
	}
	env[indx] = NULL;
	return (env);
}