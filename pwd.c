/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:44:40 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/27 16:42:20 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	int		x;
	char	env[PATH_MAX + 1];

	x = 0;
	if (getcwd(env, sizeof(env)) != NULL) 
	{
		printf("%s\n", env);
		while (cwd[x])
		{
			env[x] = 0;
			x++;
		}
	}
	else
		perror("Minishell$> pwd() error!"); //message needs to be changed, otherwise, this function should work.
}