/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:02:11 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/09 19:33:30 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, char *s, int n)
{
	int	i;

	i = 0;
	while ((s[i] != '\0') && (i < n))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(t_mnshll *mnshll, char *s, int n)
{
	char	*cs;

	cs = (char *)malloc(sizeof(char) * (n + 1));
	if (!cs)
	{
		printf("Minishell: Malloc error!\n");
		return (NULL);
	}
	cs = ft_strncpy(cs, s, n);
	return (cs);
}
void	free_arrays(char **str_tab, int i)
{
	int	j;

	j = 0;
	while (j < i && str_tab[j] != 0)
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
	return (NULL);
}