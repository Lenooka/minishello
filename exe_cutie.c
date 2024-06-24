/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cutie.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:37:59 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/24 20:24:58 by otolmach         ###   ########.fr       */
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

	indx = 0;
	access_result = 0;
	while (array[indx])
	{
		temp = ft_strjoin(array[indx], "/");
		buf = ft_strjoin(temp, cmd);
		access_result = access(buf, F_OK);
		if (access_result == 0)
		{
			access_result = perm_and_isdir(minsh, buf, array);
			free(buf);
			free(temp);
			return (access_result);
		}
		free(temp);
		free(buf);
		indx++;
	}
	minsh->exit = 127;
	return (1);
}

char	**direc_from_path(t_envl *tmp)
{
	char	**result;
	char	**dir;
	int		indx;

	indx = 0;
	result = ft_split(tmp->content + 5, ':');
	dir = malloc(sizeof(char *) * (size_of_2d(result) + 1));
	if (!dir)
		return (NULL);
	while (indx < size_of_2d(result))
	{
		dir[indx] = ft_strjoin(result[indx], "/");
		indx++;
	}
	dir[indx] = NULL;
	free_all_arrays(result);
	return (dir);
}

char	**retrive_path_dir(t_envl **env, char *s)
{
	char	**direc;
	t_envl	*tmp;

	if (cmpr_cutlines(s) == 1)
		return (retrive_rel_abs_path(s));
	tmp = *env;
	while (tmp && ft_strncmp(tmp->identificator, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	direc = direc_from_path(tmp);
	return (direc);
}

void	executie_ve(t_mnshll *minsh, char *path, char **array)
{
	char	**env;
	char	**cm_rem;

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
	ft_putstr_fd("Error: execve failed\n", STDERR_FILENO);
	free_all_arrays(minsh->com_array);
	free_exit_procces(minsh, array[0]);
}

void	exe_cutie(t_mnshll *minsh, char **array)
{
	char	**split_pathvar;
	char	*path;

	if (!array || !array[0] || !array[0][0])
		free_exit_procces(minsh, NULL);
	if (isbuilt(array[0]) == 1)
		built_ex(minsh, array);
	if (g_global == SIGPIPE)
		free_exit_procces(minsh, "Error: Broken pipe\n");
	if (isbuilt(array[0]) == 1)
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
	executie_ve(minsh, path, array);
}
