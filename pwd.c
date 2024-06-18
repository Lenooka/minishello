/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:44:40 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/15 20:56:02 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	int		x;
	char	env[4096 + 1];

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