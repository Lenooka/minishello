/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:41:45 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/24 18:13:55 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_path(t_envl **envl, char *oldpath)
{
	t_envl	tmp;
	char	newpath[PATH_MAX + 1];

	tmp = *envl;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (ft_strcmp((char *)(tmp)->identificator, "PWD") == 0)
		{
			getcwd(newpath, sizeof(newpath));
			free((tmp)->content);						//Invalid free????
			(tmp)->content = ft_strdup(newpath);
			ft_bzero(newpath, ft_strlen(newpath));
			break ;
		}
		tmp = (tmp)->next;
	}
	change_oldpath(envl, oldpath);
}

void	enter_dir(t_mnshll mini, char *env)
{
	size_t	len;
	char	*new_env;

	len = ft_strlen(env) - 2;
	new_env = ft_substr(env, 2, len);
	if (chdir(new_env) == -1)
	{
		error;		//Free, errors, bla bla new_env needs to be freed if you exit here
		ms->exit = 1;
	}
	free(new_env);
}

char	*find_default(t_envl **envl)
{
	t_envl	*tmp;

	tmp = *envl;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp((char *)(tmp)->identificator, "HOME") == 0)
			return ((tmp)->content)
		tmp = (tmp)->next;
	}
	return (NULL);
}

void	cd_default(t_mnshll mini)
{
	char	*default;

	default = find_default(mini->env)
	if (!default)
	{
		error;		//Need free, exit and error functions
		mini->exit = 1;
	}
	else
	{
		if (chdir(default) == -1)
		{
			error;				//Need free, exit and error functions
			ms->exit = 1;
		}
	}
}

void	cd(t_mnshll mini, char **env)
{
	char	oldenv[PATH_MAX + 1];
	
	getcwd(oldenv, sizeof(oldenv))
	if (env && size_of_2d(env) > 2)
	{
		error;						//Need free, exit and error functions duh.
		mini->exit = 1; 
	}
	else if (!env || !env[1] || !env[1][0])
		cd_default(mini);			//need to make
	else if (env[1][0] == '~' && env)
	{
		cd_default(mini)
		if (env[1][1] == '/' && env[1][2])
			enter_dir(mini, env[1]);
	}
	else if (chdir(env[1]) == -1)
	{
		error;						//Need free, exit and error functions, duh.
		mini->exit = 1;
	}
	change_path(mini->env, oldenv);
	ft_bzero(oldenv, ft_strlen(oldenv));
}
