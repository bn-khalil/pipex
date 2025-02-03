/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:58:49 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/03 16:17:44 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	execution_child(int fds[], char *filename, \
char **env, char *command)
{
	int	infd;

	infd = open(filename, O_RDONLY);
	if (infd < 0)
	{
		close_all_unused_fds();
		put_message("Error: no such file or directory\n");
	}
	dup2(infd, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close_all_unused_fds();
	execute_command(command, env);
}

static void	execution_parent(int fds[], char *filename, \
char **env, char *command)
{
	int	outfd;

	outfd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (outfd < 0)
	{
		close_all_unused_fds();
		put_message("Error: no such file or directory\n");
	}
	dup2(fds[0], STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	close_all_unused_fds();
	execute_command(command, env);
}

static pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close_all_unused_fds();
		put_message("Error: fork()\n");
	}
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	pid;
	pid_t	pid2;

	if (ac != 5)
		put_message("Error: invalid arguments\n");
	if (!env)
		put_message("Error: no environment variables!\n");
	if (pipe(fds) == -1)
		put_message("Error: pipe\n");
	pid = ft_fork();
	if (pid == 0)
		execution_child(fds, av[1], env, av[2]);
	pid2 = ft_fork();
	if (pid2 == 0)
		execution_parent(fds, av[4], env, av[3]);
	close_all_unused_fds();
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
