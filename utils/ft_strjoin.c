/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:29:23 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/25 10:32:01 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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