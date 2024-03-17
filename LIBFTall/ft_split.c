/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:42:53 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/07 15:42:54 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*ft_strncpy(char *dest, const char *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s[i] != '\0') && (i < n))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*cs;

	cs = (char *)malloc(sizeof(char) * (n + 1));
	if (!cs)
	{
		return (NULL);
	}
	cs = ft_strncpy(cs, s, n);
	return (cs);
}

static char	**ft_free(char **str_tab, int i)
{
	int	j;

	j = 0;
	while (j < i && str_tab[j] != 0)
	{
		free(str_tab[j]);
		j++;
	}
	free(str_tab);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	int			i;
	char		**result;
	const char	*start;

	i = 0;
	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			start = s;
			while (*s && *s != c)
				s++;
			result[i++] = ft_strndup(start, s - start);
			if (!result[i - 1])
				return (ft_free(result, i));
		}
	}
	result[i] = NULL;
	return (result);
}
