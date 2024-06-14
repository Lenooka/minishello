/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:41:45 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/14 19:46:58 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//removed the tmp check for Null, if issue hi.

void	change_path(t_envl **envl, char *oldpath)
{
	t_envl	*tmp;
	char	newpath[PATH_MAX + 1];
	int		x;

	x = 0;
	tmp = *envl;
	while (tmp && !x)
	{
		if (ft_strcmp((tmp)->identificator, "PWD") == 0)
		{
			getcwd(newpath, sizeof(newpath));
			free((tmp)->content);
			(tmp)->content = ft_strdup(newpath);
			ft_bzero(newpath, ft_strlen(newpath));
			x++;
		}
		if (!x)
			tmp = (tmp)->next;
	}
	change_oldpath(envl, oldpath);
}

void	enter_dir(t_mnshll *mini, char *env)
{
	size_t	len;
	int		x;
	char	*new_env;

	len = ft_strlen(env);
	new_env = ft_substr(env, 2, len - 2);
	x = chdir(new_env);
	if (x == -1)
	{
		error_msg(mini, "No such file or directory", 1, "cd");
		mini->exit = 1;
	}
	if (!new_env)
		return ;
	free(new_env);
}

/*
char	*find_default(t_envl **envl)
{
	t_envl	*tmp;

	tmp = *envl;
	while (tmp)
	{
		if (ft_strcmp((tmp)->identificator, "HOME") == 0)
			return ((tmp)->content);
		tmp = (tmp)->next;
	}
	return (NULL);
}
*/

char	*find_default(t_envl **envl)
{
	while (*envl)
	{
		if (ft_strcmp((*envl)->identificator, "HOME") == 0)
			return ((*envl)->content);
		*envl = (*envl)->next;
	}
	return (NULL);
}

void	cd_default(t_mnshll *mini)
{
	char	*def;
	int		x;

	x = 0;
	def = find_default(mini->envl);
	if (!def)
		error_msg(mini, "Home not set", 1, "cd");
	else
		x = chdir(def);
	if (x == -1)
	{
		error_msg(mini, "No such file or directory", 1, "cd");
		mini->exit = 1;
	}
}

void	cd(t_mnshll *mini, char **env)
{
	char	oldenv[PATH_MAX + 1];

	getcwd(oldenv, sizeof(oldenv));
	if (env && size_of_2d(env) > 2)
	{
		error_msg(mini, "too many arguments", 1, "cd");
		mini->exit = 1;
		return ;
	}
	if (!env || !env[1] || !env[1][0] || (env[1][0] == '~' && env))
	{
		cd_default(mini);
		if (env && env[1] && env[1][0])
		{
			if (env[1][0] == '~' && env[1][1] == '/' && env[1][2] && env) 
				enter_dir(mini, env[1]);
		}
	}
	else if (chdir(env[1]) == -1)
	{
		error_msg(mini, "No such file or directory", 1, "cd");
		mini->exit = 1;
	}
	change_path(mini->envl, oldenv);
	ft_bzero(oldenv, ft_strlen(oldenv));
}
