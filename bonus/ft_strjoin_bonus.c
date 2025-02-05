/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:29:23 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/05 13:08:23 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		strlen;
	char	*str;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * strlen + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	strlen = 0;
	while (s2[strlen])
		str[i++] = s2[strlen++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_opner_file(int status, char *filename)
{
	int	fd;

	fd = -1;
	if (status == 2)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (status == 3)
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (status == 5)
		fd = open(filename, O_RDONLY);
	return (fd);
}

void	close_all_unused_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < OPEN_MAX)
	{
		close(fd);
		fd++;
	}
}
