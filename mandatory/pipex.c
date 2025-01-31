/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:58:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/31 17:08:24 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void execution_child(int fds[], char *filename, char **env, char *command)
{
    int infd;

    infd = open(filename, O_RDONLY);
    if (infd < 0)
    {
        ft_closer(fds[0], fds[1], -1, -1);
        put_message("Error: no such file or directory\n");
    }
    close(fds[0]);
    dup2(infd, STDIN_FILENO);
    close(infd);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    execute_command(command, env);
}

static void execution_parent(int fds[], char *filename, char **env, char *command)
{
    int outfd;

    outfd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (outfd < 0)
    {
        ft_closer(fds[0], fds[1], -1, -1);
        put_message("Error: no such file or directory\n");
    }
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    dup2(outfd, STDOUT_FILENO);
    close(outfd);
    execute_command(command, env);
}

void    f()
{
    system("leaks pipex; lsof -c pipex");
}

int main(int ac, char **av, char **env)
{
    int fds[2];
    int pid;
    int pid2;

    atexit(f);
    if (ac != 5)
        put_message("Error: invalid arguments\n");
    if (!env || !env[0])
        put_message("Error: no environment variables!\n");
    if (pipe(fds) == -1)
        put_message("Error: pipe\n");
    pid = fork();
    if (pid < 0)
    {
        ft_closer(fds[0], fds[1], -1, -1);
        put_message("Error: fork()\n");
    }
    if (pid == 0)
        execution_child(fds, av[1], env, av[2]);
    pid2 = fork();
    if (pid2 == 0)
        execution_parent(fds, av[4], env, av[3]);
    ft_closer(fds[0], fds[1], -1, -1);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
