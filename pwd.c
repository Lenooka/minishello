/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:44:40 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/26 05:47:58 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	int		i;
	char	env[PATH_MAX + 1];

	i = 0;
	if (getcwd(env, sizeof(env)) != NULL) 
	{
		printf("%s\n", env);
		while (cwd[i])
			env[i++] = 0;
	}
	else
		perror("Minishell$> pwd() error!"); //message needs to be changed, otherwise, this function should work.
}