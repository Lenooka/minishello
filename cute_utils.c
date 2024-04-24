/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:19:24 by olena             #+#    #+#             */
/*   Updated: 2024/04/24 18:20:38 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
