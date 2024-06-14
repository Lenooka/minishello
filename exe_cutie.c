/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cutie.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:37:59 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/14 14:07:27 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handle relative and absolute path
if getcwd fails return NULL
if cmd starts with ../ or ./ or / join with / and return
else return NULL
*/

int	check_executie(t_mnshll *minsh, char **array, char *cmd)
{
	int		indx;
	char	*temp;
	char	*buf;
	int		access_result;
	int		result;

	indx = 0;
	result = 0;
	while (array[indx])
	{
		temp = ft_strjoin(array[indx], "/");
		buf = ft_strjoin(temp, cmd);
		free(temp);
		access_result = access(buf, F_OK);
		if (access_result == 0)
		{
			result = perm_and_isdir(minsh, buf, array);
			free(buf);
			return (result);
		}
		free(buf);
		indx++;
	}
	minsh->exit = 127;
	return (1);
}

int	cmpr_cutlines(char *s)
{
	int	res;

	res = 0;
	if (ft_strncmp(s, "../", 3) == 0)
		res = 1;
	else if (ft_strncmp(s, "./", 2) == 0)
		res = 1;
	else if (s[0] == '/')
		res = 1;
	return (res);
}

char	**retrive_path_dir(t_envl **env, char *s)
{
	int		indx;
	char	**result;
	char	**direc;
	t_envl	*tmp;

	indx = 0;
	if (cmpr_cutlines(s) == 1)
		return (retrive_rel_abs_path(s));
	tmp = *env;
	while (tmp && ft_strncmp(tmp->identificator, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	result = ft_split(tmp->content + 5, ':');
	direc = malloc(sizeof(char *) * (size_of_2d(result) + 1));
	if (!direc)
		return (NULL);
	while (indx < size_of_2d(result))
	{
		direc[indx] = ft_strjoin(result[indx], "/");
		indx++;
	}
	direc[indx] = NULL;	
	free_all_arrays(result);
	return (direc);
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

void	executie_ve(t_mnshll *minsh, char *path, char **cm_rem, char **array)
{
	char	**env;

	env = convert_env(minsh->envl);
	if (env == NULL)
		free_exit_procces(minsh, "Error: env conversion failed \n");
	cm_rem = rem_q_from_2d(array);
	if (cm_rem == NULL)
		free_exit_procces(minsh, "Error: command conversion failed\n");
	execve(path, cm_rem, env);
	minsh->exit = errno;
	free_all_arrays(env);
	free_all_arrays(cm_rem);
	free_exit_procces(minsh, array[0]);
}

void	exe_cutie(t_mnshll *minsh, char **array, char **new_cmd)
{
	char	**split_pathvar;
	char	*path;

	if (!array || !array[0] || !array[0][0])
		free_exit_procces(minsh, NULL);
	if (isbuilt(array[0]) == 1)
		built_ex(minsh, array);
	if (g_global == SIGPIPE)
		free_exit_procces(minsh, "Error: Broken pipe\n");
	if ((!array || !array[0] || !array[0][0]) || isbuilt(array[0]) == 1)
		free_exit_procces(minsh, NULL);
	split_pathvar = retrive_path_dir(minsh->envl, array[0]);
	if (split_pathvar == NULL)
		free_exit_procces(minsh, "Error: path not found\n");
	if (check_executie(minsh, split_pathvar, array[0]) == 0)
		free_exit_procces(minsh, NULL);
	path = find_ex_path(minsh, split_pathvar, array[0]);
	if (path == NULL)
	{
		free_all_arrays(split_pathvar);
		free_exit_procces(minsh, NULL);
	}
	free_all_arrays(split_pathvar);
	executie_ve(minsh, path, new_cmd, array);
}
