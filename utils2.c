/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:54 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/09 15:51:37 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int little_skip_quotes(char *str, int x, int len)
{
    char    c;

    c = str[x];
    x++;
    while (x < len && str[x] != c)
        x++;
    if (x < len)
        x++;
    return (x);
}