/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:41:45 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/21 18:54:37 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_mnshll mini, char **env)
{
	char	oldpath[PATH_MAX + 1];
	
	getcwd(oldpath, sizeof(oldpath))
	if (env && arr_size(env) > 2)
	{
		error;						//Need free, exit and error functions duh.
		ms->error; 
	}

}