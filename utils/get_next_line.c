/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:23:41 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/27 22:51:35 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*get_next_line(int fd)
{
	char	*buff;
	int		readed;
	char	*line;

	line = NULL;
	buff = malloc(2);
	if (!buff)
		return (NULL);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buff, 1);
		if (readed == 0)
			break ;
		buff[readed] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(buff);
	return (line);
}
