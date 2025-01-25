/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:58:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/25 20:11:53 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char *get_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strnstr(env[i], "PATH", ft_strlen("PATH")))
            return (env[i]);
        i++;
    }
    return (NULL);
}

static char *get_path_command(char *command, char **env, char **cmd_flags)
{
    char *path;
    char **directions;
    char *path_command;
    int i;

    i = 0;
    path = get_path(env);
    if (!path)
    {
        ft_free_2d(cmd_flags);
        put_message("Error:\nPATH\n",2);
    }
    path = path + 5;
    directions = ft_split(path, ':');
    if (!directions)
    {
        ft_free_2d(cmd_flags);
        put_message("Error:\nPATH\n",2);
    }
    while (directions[i])
    {
        directions[i] = ft_strjoin(directions[i], "/");
        directions[i] = ft_strjoin(directions[i], command);
        if ((access(directions[i], F_OK)) == 0)
        {
            path_command = ft_strdup(directions[i]);
            ft_free_2d(directions);
            return (path_command);
        }
        i++;
    }
    ft_free_2d(directions);
    return (NULL);
}


static void execute_command(char *command, char **env)
{
    char **cmd_flag;
    char *command_path;

    if (ft_strchr(command, '/'))
        put_message("No such file or directory\n", 2);
    cmd_flag = ft_split(command, ' ');
    if (!cmd_flag)
        put_message("command not found!\n", 2);
    
    command_path = get_path_command(cmd_flag[0], env, cmd_flag);
    if (!command_path)
    {
        ft_free_2d(cmd_flag);
        put_message("command not found!\n", 2);
    }
    if (execve(command_path, cmd_flag, NULL) == -1)
        put_message("command not found!\n", 2);
    ft_free_2d(cmd_flag);
    free(command_path);
}

static void execution_child(int fds[], int infd, char **env, char *command)
{
    close(fds[0]);
    dup2(infd, STDIN_FILENO);
    close(infd);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    execute_command(command, env);
}

static void execution_parent(int fds[], int outfd, char **env, char *command)
{
    close(fds[1]);
    dup2(outfd, STDOUT_FILENO);
    close(outfd);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    execute_command(command, env);
}

int main(int ac, char **av, char **env)
{
    int fds[2];
    int pid;
    int infd;
    int outfd;

    pid = 0;
    if (ac != 5)
        put_message("Error:\ninvalid arguments\n",2);
    if (!env)
        put_message("Error:\nno environment variables!\n", 2);
    infd = open(av[1], O_CREAT | O_RDWR, 0777);
    if (!infd)
        put_message("Error:\ncan't read from input file!\n", 2);
    outfd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (!outfd)
        put_message("Error:\ncan't write in output file!\n", 2);
    if (pipe(fds) == -1)
        put_message("Error: pipe\n",2);
    pid = fork();
    if (pid < 0)
        put_message("Error: fork()\n", 2);
    if (pid == 0)
    {
        close(outfd);
        execution_child(fds, infd, env, av[2]);
    }
    else
    {
        close(infd);
        execution_parent(fds, outfd, env, av[3]);
    }
    return (0);
}
