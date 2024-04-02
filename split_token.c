/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:11 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/02 18:53:12 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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


char	**split_tokenize(t_mnshll *minsh, char *str)
{
	char	**result;
	int		token_ammount;
	int		i;
	int		toklen;

	i = 0;
	token_ammount = count_words(minsh) + 1;
	result = (char **)malloc(sizeof(char *) * (token_ammount));
	if (!result)
		return (NULL);
	while (i < token_ammount - 1)
	{
		if (*str && parser_codes(*str) == 3)
			str++;
		else
		{
			toklen = ft_toklen(str);
			result[i++] = ft_strndup(str, toklen);
			if (!result[i - 1])
				return (free_arrays(result, i));
			str = str + toklen;
		}
	}
	result[i] = NULL;
	return (result);
}