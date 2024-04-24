/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cutie.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:37:59 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/23 22:28:58 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Handle relative and absolute path
if getcwd fails return NULL
if cmd starts with ../ or ./ or / join with / and return
else return NULL
*/
char	**retrive_rel_abs_path(const char *cmd)
{
	char	**result;
	char	buf[PATH_MAX + 1];

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	ft_bzero(buf, PATH_MAX + 1);
	if (ft_strnstr(cmd, "../", 3) || ft_strnstr(cmd, "./", 2) == 0)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			free(result);
			return (NULL);
		}
		result[0] = ft_strjoin(buf, "/");
		ft_bzero(buf, ft_strlen(buf));
	}
	if (cmd[0] == '/')
		result[0] = ft_strjoin(NULL, "/");
	result[1] = NULL;
	return (result);
}


char   *find_ex_path(t_mnshll *minsh, char **array, char *cmd)
{
	int		indx;
	char	*temp;
	char	*buf;
	int		acsess_result;

	indx = 0;
	acsess_result = 0;
	while (array[i])
	{
		temp = ft_strjoin(array[i++], "/");
		buf = ft_strjoin(temp, cmd);
		free(temp);
		acsess_result = access(buf, F_OK);
		if (acsess_result == 0)
			return (buf);
		free(buf);
	}
	return (NULL);
}
/*
Check if the com path is a dir or has exec permi.
If is a dir, error message and set exit status to 126.
If no exec perm,  error message and set exit to 126.
If no access to path, error message and set exit to 1.
 */
int perm_and_isdir(t_mnshll *minsh, char *cmd_path, char **array)
{
	struct stat path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		minsh->exit = 126;
	}
	else if (access(cmd_path, X_OK) == 0)
	{
		free(cmd_path);
		return (1);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		perror("Minishell: error: ");
		minsh->exit = 126;
	}
	else
		minsh->exit = 1;
	free(cmd_path);
	free_all_arrays(array);
	return (0);
}


int check_executie(t_mnshll *minsh, char **array, char *cmd)
{
	int indx;
	char *temp;
	char *buf;
	int access_result;
	int result;

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
	return (1);
}

char    **retrive_path_dir(char **env, char *s)
{
    int		indx;
	char	**result;
	char	**direc;
	t_envl 	*tmp;

	indx = 0;
	if (ft_strnstr(s, "../", 3) || ft_strnstr(s, "./", 2) == 0 || s[0] == '/')
		return (retrive_rel_abs_path(str));
	tmp = *env;
	while (tmp && ft_strnstr(tmp->identificator, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	result = ft_split(tmp->content + 5, ':');
	direc = malloc(sizeof(char *) * (size_of_2d(result) + 1))
	if (!direc)
		return (NULL);
	while (indx < size_of_2d(result))
	{
		direc[indx] = ft_strjoin(result[indx], "/");
		indx++;
	}
	direc[indx] == NULL;
	free_all_arrays(result);
	return (direc);	
}

void	executie_ve(char *path, char **new_cmnd, char **env)
{
	env = //get array from env list if its works :< it doess!!! just need to write a function for it
	new_cmnd = 
	if (execve(path, new_cmd, env) == -1)
		//error handle
	//exit status??
	//free exit process
}

void	exe_cutie(t_mnshll *minsh, char **array, char **new_cmd)
{
	char	**split_pathvar;
	char	*path;
	char	**env;

	if (!array || !array[0] || !array[0][0])
		//error command not found NULL exit process here?? 		//no exit in next check
	if (isbuilt(array[0]) == 1)
		//function where we ft_cmpr string and execute built ins //do we exit the procces here??		//no exit in next check
	if (g_global == SIGPIPE)
		//free exit process
	if (!array || !array[0] || !array[0][0] || isbuilt(array[0]) == 1)
		//free exit process
	split_pathvar = retrive_path_dir(minsh->env, array[0]); //done
	if (split_pathvar == NULL)
		 //god please tell me env is finee
	if (check_executie(minsh, split_pathvar, array[0]) == 0) //done
		//free exit process
	path = find_ex_path(minsh, split_pathvar, array[0]); //simmilar to pipex?? DONE
	free_all_arrays(split_pathvar); //this in functuin find ex path
	if (!path)
	 //free maybe should do it in find expath
	executie_ve(path, new_cmd, env);
}


