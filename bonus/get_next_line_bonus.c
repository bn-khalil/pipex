/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:58:15 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/05 13:25:48 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

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
