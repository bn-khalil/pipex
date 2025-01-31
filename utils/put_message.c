/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:23:07 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/31 17:04:25 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void put_message(char *msg)
{
    write(2, msg, ft_strlen(msg));
    if (ft_strncmp(msg, "command not found!", \
    ft_strlen("command not found!")) == 0)
          exit(127);
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

void ft_closer(int read_end , int write_end, int infd, int outfd)
{
     if (read_end != -1)
          close(read_end);
     if (write_end != -1)
          close(write_end);
     if (infd != -1)
          close(infd);
     if (outfd != -1)
          close(outfd);
}

void put_and_free(char *msg, char **content)
{
     ft_free_2d(content);
     put_message(msg);
}