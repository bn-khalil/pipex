/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:22:11 by kben-tou          #+#    #+#             */
/*   Updated: 2025/01/29 13:03:45 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char *get_path(char **env)
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

static char *ft_joiner(char **direction, char *command)
{
    int i;

    i = 0;
    while (direction[i])
    {
        direction[i] = ft_strjoin(direction[i], "/");
        if (!direction[i])
            return (NULL);
        direction[i] = ft_strjoin(direction[i], command);
        if (!direction[i])
            return (NULL);
        if ((access(direction[i], F_OK)) == 0)
            return (ft_strdup(direction[i]));
        i++;
    }
    return (NULL);
}

// char *get_path_command(char *command, char **env, char **cmd_flags)
// {
//     char *path;
//     char **directions;
//     char *path_command;
//     int i;

//     i = -1;
//     path = get_path(env);
//     if (!path)
//         put_and_free("Error: PATH!\n", cmd_flags);
//     directions = ft_split(path + 5, ':');
//     if (!directions || !directions[0])
//         put_and_free("Error: PATH!\n", cmd_flags);
//     while (directions[++i])
//     {
//         directions[i] = ft_joiner(directions[i], command);
//         if (!directions[i])
//             break ;
//         if ((access(directions[i], F_OK)) == 0)
//         {
//             path_command = ft_strdup(directions[i]);
//             ft_free_2d(directions);
//             return (path_command);
//         }
//     }
//     ft_free_2d(directions);
//     return (NULL);
// }



char *get_path_command(char *command, char **env, char **cmd_flags)
{
    char *path;
    char **directions;
    char *command_path;

    path = get_path(env);
    if (!path)
        put_and_free("Error: PATH!\n", cmd_flags);
    directions = ft_split(path + 5, ':');
    if (!directions || !directions[0])
        put_and_free("Error: PATH!\n", cmd_flags);
    command_path = ft_joiner(directions, command);
    ft_free_2d(directions);
    if (!command_path)
        return (NULL);
    return (command_path);
}

char *parse_command(char *command)
{
    if (!command || !command[0])
        put_message("permission denied\n");
    if (command[0] == ' ' || command[ft_strlen(command) - 1] == ' ')
        put_message("command not found!\n");
    return (command);
}

void execute_command(char *command, char **env)
{
    char **cmd_flag;
    char *path_command;

    command = parse_command(command);
    cmd_flag = ft_split(command, ' ');
    if (!cmd_flag || !cmd_flag[0])
        put_message("command not found!\n");
    if (cmd_flag[0][0] == '/')
    {
        if ((access(cmd_flag[0], F_OK)) != 0)
            put_and_free("Error: No such file or directory\n", cmd_flag);
        path_command = cmd_flag[0];
    }
    else
    {
        if (cmd_flag[0][0] == '.')
            put_and_free("Error: No such file or directory\n", cmd_flag);
        path_command = get_path_command(cmd_flag[0], env, cmd_flag);
        if (!path_command)
            put_and_free("command not found!\n", cmd_flag);
    }
    execve(path_command, cmd_flag, env);
    put_and_free("command not found!\n", cmd_flag);
}
