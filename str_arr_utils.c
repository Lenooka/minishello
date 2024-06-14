/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:10:26 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/11 19:56:15 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '$')
		return (0);
	i++;
	if (str[i] && (str[i] == '?' || ft_isdigit(str[i])))
		return (2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	**duplicate_string_array(t_mnshll *minsh, char **old_arr)
{
	int		size;
	char	**result;
	int		i;

	i = 0;
	size = size_of_2d(old_arr);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
	{
		printf("Malloc fail!\n");
		return (NULL);
	}
	while (old_arr && old_arr[i])
	{
		result[i] = ft_strndup(minsh, old_arr[i], ft_strlen(old_arr[i]));
		i++;
	}
	result[i] = NULL;
	free_all_arrays(old_arr);
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
	while (str_tab[j])
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
}
