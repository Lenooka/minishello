/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cutie.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:37:59 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/19 21:18:08 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executie_ve(char *path, char **new_cmnd, char **env)
{
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
		//error command not found NULL exit process here??
		//no exit in next check
	if (isbuilt(array[0]) == 1)
		//function where we ft_cmpr string and execute built ins //do we exit the procces here??
		//no exit in next check
	if (g_global == SIGPIPE)
		//free exit process
	if (!array || !array[0] || !array[0][0] || isbuilt(array[0]) == 1)
		//free exit process
	split_pathvar = retrive_path_dir(minsh->env, array[0]); //god please tell me env is finee
	if (check_executie(minsh, split_pathvar, array[0]))
		//free exit process
	path = find_ex_path(minsh, split_pathvar, array[0]); //simmilar to pipex??
	free_all_arrays(split_pathvar); //this in functuin find ex path
	if (!path)
	 //free maybe should do it in find expath
	env = //get array from env list if its works :( it doess!!! just need to write a function for it
	new_cmd = 
	executie_ve(path, new_cmd, env);
}


