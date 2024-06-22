/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:19:24 by olena             #+#    #+#             */
/*   Updated: 2024/06/22 19:51:11 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**retrive_rel_abs_path(const char *cmd)
{
	char	**result;
	char	buf[4096 + 1];

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	ft_bzero(buf, 4096 + 1);
	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2) == 0)
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
	{
		result[0] = ft_strjoin(buf, "/");
	}
	result[1] = NULL;
	return (result);
}

char	*find_ex_path(t_mnshll *minsh, char **array, char *cmd)
{
	int		indx;
	char	*temp;
	char	*buf;

	indx = 0;
	cmd = remove_quotes(cmd);
	while (array && array[indx])
	{
		temp = ft_strjoin(array[indx], "/");
		buf = ft_strjoin(temp, cmd);
		free(temp);
		if (access(buf, 0) == 0)
			return (buf);
		free(buf);
		indx++;
	}
	if (ft_strchr(cmd, '/'))
		perror(cmd);
	else if (ft_strcmp(cmd, "\'\'") != 0 && ft_strcmp(cmd, "\"\"") != 0)
	{
		printf("Error: %s: command not found!\n", cmd);
		minsh->exit = 127;
		return (free(cmd), NULL);
	}
	return (NULL);
}
/*
Check if the com path is a dir or has exec permi.
If is a dir, error message and set exit status to 126.
If no exec perm,  error message and set exit to 126.
If no access to path, error message and set exit to 1.
 STAT : Get file attributes for FILE and put them in BUF.  */


int	perm_and_isdir(t_mnshll *minsh, char *cmd_path, char **array)
{
	struct stat	path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		minsh->exit = 126;
	}
	else if (access(cmd_path, X_OK) == 0)
	{
		return (1);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		perror("Error: ");
		minsh->exit = 126;
	}
	else
		minsh->exit = 1;
	free_all_arrays(array);
	return (0);
}
