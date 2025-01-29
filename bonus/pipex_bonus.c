/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:28:24 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/29 13:14:31 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void child_process(char *command, char **env)
{
    int pid;
    int fds[2];

    if (pipe(fds) == -1)
        put_message("Error: pipe\n");
    pid = fork();
    if (pid < 0)
    {
        ft_closer(fds[0], fds[1], -1, -1);
        put_message("Error: fork()\n");
    }
    if (pid == 0)
    {
        dup2(fds[1], STDOUT_FILENO);
        ft_closer(fds[0], fds[1], -1, -1);
        execute_command(command, env);
    }
    else
    {
        dup2(fds[0], STDIN_FILENO);
        ft_closer(fds[0], fds[1], -1, -1);
        waitpid(pid, NULL, 0);
    }
}

void pipeline(int i, int ac, char **av, char **env)
{
    int infd;
    int outfd;

    infd = 0;
    outfd = 0;
    infd = open(av[1], O_RDONLY);
    if (infd < 0)
        put_message("Error: no such file or directory\n");
    outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (outfd < 0)
    {
        close(infd);
        put_message("Error: no such file or directory\n");
    }
    dup2(infd, STDIN_FILENO);
    close(infd);
    while (i < ac - 2)
    {
        child_process(av[i], env);
        i++;
    }
    dup2(outfd, STDOUT_FILENO);
    close(outfd);
    execute_command(av[ac - 2], env);
}

void read_and_fill(char *line, char **av, int fds[])
{
    while (1)
    {
        write(STDIN_FILENO, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line)
            break ;
        if (ft_strncmp(av[2], line, ft_strlen(av[2])) == 0 )
        {
            free(line);
            ft_closer(fds[0], fds[1], -1, -1);
            exit(EXIT_FAILURE);
        }
        write(fds[1], line, ft_strlen(line));
        free(line);
    }
}

void here_doc(char **av)
{
    char *line;
    int fds[2];
    pid_t pid;

    line = NULL;
    if (pipe(fds) == -1)
        put_message("Error: pipe\n");
    pid = fork();
    if (pid == 0)
        read_and_fill(line, av, fds);
    else
    {
        dup2(fds[0], STDIN_FILENO);
        ft_closer(fds[0], fds[1], -1, -1);
        waitpid(pid, NULL, 0);
    }
}

int main(int ac, char **av, char **env)
{
    int i;
    int outfd;

    i = 2;
    if (ac < 5)
        put_message("Error: invalid arguments!\n");
    if (!env || !env[0])
        put_message("Error: no environment variables!\n");
    if (ft_strncmp("here_doc", av[1], ft_strlen("here_doc")) == 0)
    {
        here_doc(av);
        while (++i < ac - 2)
            child_process(av[i], env);
        outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (outfd < 0)
            put_message("no such file or directory\n");
        dup2(outfd, STDOUT_FILENO);
        close(outfd);
        execute_command(av[ac - 2], env);
    }
    else
        pipeline(i , ac, av, env);
    return (0);
}
