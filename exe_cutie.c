/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cutie.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:37:59 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/19 18:14:33 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_all_arrays()
	
}


