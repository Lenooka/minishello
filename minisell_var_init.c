/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisell_var_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:26:39 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/26 18:27:03 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_mnshll	*mnshll_init(t_mnshll *mnshll, char **env)
{
	int	i;

	i = 0;
	if (!env || env[0][0] == '\0')
		return (NULL); //error handle????;
	mnshll = malloc(sizeof(t_mnshll));
 	if (!mnshll)
  		return (NULL);
 	mnshll->envl = env_list_init(env, i);
	if (!mnshll->envl)
		return (NULL);
 	mnshll->exit = 0;
	return (mnshll);
}