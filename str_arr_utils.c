/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:10:26 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/09 20:06:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_string_array(t_mnshll *minsh, char **old_arr)
{
	int		size;
	char	**result;
	int		i;

	i = 0;
	size = size_of_2d(old_arr) + 1;
	result = malloc(sizeof(char *) * (size));
	if (!result)
		//should we free exit after every malloc/open/fork fail???
	while (old_arr && old_arr[i])
	{
		result[i] = ft_strdup(old_arr[i]);
		i++;	
	}
	result[i] == NULL;
	return (result);
}

int	size_of_2d(char **arr)
{
	int	i;
	int	count;

	if (!arr)
		return (0);
	i = 0;
	count = 0;
	while (arr[i])
	{
		if (arr[i][0])
			count++;
		i++;
	}
	return (count);
}

void	free_all_arrays(char **str_tab)
{
	int	j;

	j = 0;
	if (!str_tab)
		return ;
	while (str_tab[j] != 0)
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
}