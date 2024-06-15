/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:06:37 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/15 16:28:09 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(t_mnshll *minsh, char *msg, int exit_code, char *com)
{
	if (exit_code == 1 && msg)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(com, STDERR_FILENO);
		exit_code = 1;
	}
	else if (exit_code == 2)
	{
		printf("Error: Malloc error\n");
		free(minsh);
		exit(12);
	}
}

void	change_oldpath(t_envl **envl, char *oldpath)
{
	t_envl	*tmp;
	char	*new_content;

	tmp = *envl;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (strcmp((char *)(tmp)->identificator, "OLDPWD") == 0)
		{
			new_content = ft_strdup(oldpath);
			free((tmp)->content);
			(tmp)->content = new_content;
			break ;
		}
		tmp = (tmp)->next;
	}
}

void	list_swap(t_mnshll *mini, t_envl *list)
{
	char	*ident;
	void	*content;
	t_envl	*top;
	t_envl	*tmp;

	ident = NULL;
	content = NULL;
	top = list;
	if (!top && !top->next)
	{
		write(2, "List Swap Error\n", 16);
		mini->exit = 1;
		return ;
	}
	tmp = top;
	ident = tmp->identificator;
	content = tmp->content;
	top->identificator = top->next->identificator;
	top->content = top->next->content;
	top->next->identificator = ident;
	top->next->content = content;
}

char	*get_ident(char *str, int c) //might need const
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == (char)c)
			break ;
	len = i + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (j < i)
	{
		res[j] = str[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*get_cont(char *str, int c) //might need const char
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] == (char)c)
			break ;
	if (i == (int)ft_strlen(str) || str[i + 1] == '\0')
		return (ft_strdup("  "));
	len = ft_strlen(str) - i + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (str[i])
		res[++j] = str[++i];
	res[j] = '\0';
	return (res);
}
