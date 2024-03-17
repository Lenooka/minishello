/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:59:22 by otolmach          #+#    #+#             */
/*   Updated: 2023/10/14 20:45:05 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_read_join(int fd, char *str)
{
	char	*buffer;
	int		rbt;

	rbt = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(str, '\n') && rbt != 0)
	{
		rbt = read(fd, buffer, BUFFER_SIZE);
		if (rbt == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[rbt] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read_join(fd, str);
	if (!str)
		return (NULL);
	line = ft_subline(str);
	str = ft_sub_new_line(str);
	return (line);
}
/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("test/empty.txt", O_RDONLY);

	i = 1;
	while (i < 2)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/
