/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_var_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:26:39 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/24 13:48:24 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mnshll	*mnshll_init(t_mnshll *mnshll, char **env)
{
	int	i;

	i = 0;
	if (!env || env[0][0] == '\0')
		return (NULL);
	mnshll = malloc(sizeof(t_mnshll));
	if (!mnshll)
		return (NULL);
	mnshll->envl = env_list_init(env, i);
	if (!mnshll->envl)
	{
		free(mnshll);
		return (NULL);
	}
	mnshll->exit = 0;
	return (mnshll);
}
