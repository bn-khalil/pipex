/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:28:24 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/31 13:28:17 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void child_process(char *command, char **env, int infd, int outfd)
{
    int pid;

    pid = fork();
    if (pid < 0)
    {
        ft_closer(infd, outfd, -1, -1);
        put_message("Error: fork()\n");
    }
    if (pid == 0)
    {
        if (infd != STDIN_FILENO)
            dup2(infd, STDIN_FILENO);
        close(infd);
        if (outfd != STDOUT_FILENO)
            dup2(outfd, STDOUT_FILENO);
        close(outfd);
        execute_command(command, env);
    }
}

int ft_opner_file(int status, char *filename)
{
    int fd;

    fd = -1;
    if (status == 2)
        fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
    else if (status == 3)
        fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
    else if (status == 4)
        fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    else if (status == 5)
        fd = open(filename, O_RDONLY);
    return (fd);
}

void pipeline(int s[], char **av, char **env, int infd)
{
    int outfd;
    int fds[2];
    int prev_in;
    int i;

    i = s[0];
    prev_in = infd;
    while (i < s[1] - 2)
    {
        if (pipe(fds) == -1)
        {
            ft_closer(prev_in, -1, infd, -1);
            put_message("Error: pipe\n");
        }
        child_process(av[i], env, prev_in, fds[1]);
        close(fds[1]);
        close(prev_in);
        prev_in = fds[0];
        i++;
    }
    outfd = ft_opner_file(s[0], av[s[1] - 1]);
    if (outfd < 0)
    {
        ft_closer(prev_in, -1, infd, -1);
        put_message("Error: no such file or directory\n");
    }
    child_process(av[i], env, prev_in, outfd);
    ft_closer(prev_in, -1, -1, outfd);
    while (wait(NULL) > 0);
}

void read_and_fill(char **av)
{
    char *line;
    int tmpfd;

    tmpfd = ft_opner_file(4, "/tmp/helper");
    if (tmpfd < 0)
        put_message("Error: no such file or directory\n");
    while (1)
    {
        write(STDIN_FILENO, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line)
            break ;
        if (ft_strncmp(av[2], line, ft_strlen(av[2])) == 0)
        {
            free(line);
            break ; 
        }
        write(tmpfd, line, ft_strlen(line));
        free(line);
    }
    close(tmpfd);
}

void here_doc(int s[], char **av, char** env)
{
    int tmpfd;

    read_and_fill(av);
    tmpfd = ft_opner_file(5, "/tmp/helper");
    if (tmpfd < 0)
        put_message("Error: no such file or directory\n");
    pipeline(s, av, env, tmpfd);
    unlink("/tmp/helper");
}

void    f()
{
    system("leaks pipex; lsof -c pipex");
}
int main(int ac, char **av, char **env)
{
    int infd;
    int start_end[2];

    atexit(f);
    start_end[0] = 2;
    start_end[1] = ac;
    if (ac < 5)
        put_message("Error: invalid arguments!\n");
    if (!env || !env[0])
        put_message("Error: no environment variables!\n");
    if (ft_strncmp("here_doc", av[1], ft_strlen("here_doc")) == 0)
    {
        if (ac != 6)
            put_message("Error: invalid arguments!\n");
        start_end[0] = 3;
        here_doc(start_end, av, env);
    }
    else
    {
        infd = open(av[1], O_RDONLY);
        if (infd < 0)
            put_message("Error: no such file or directory\n");
        pipeline(start_end, av, env, infd);
    }
    return (0);
}
