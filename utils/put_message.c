/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:23:07 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/25 19:25:17 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void put_message(char *msg, int fd)
{
    write(fd, msg, ft_strlen(msg));
    exit(EXIT_FAILURE);
}

void ft_free_2d(char **content)
{
   int i;

   i = 0;
   if (!content)
        return ;
   while (content[i])
   {
        free(content[i]);
        i++;
   }
   free(content);
}