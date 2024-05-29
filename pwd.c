/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:44:40 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/29 17:19:56 by otolmach         ###   ########.fr       */
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
		while (env[x])
		{
			env[x] = 0;
			x++;
		}
	}
	else
		perror("pwd:"); //message needs to be changed, otherwise, this function should work.
}