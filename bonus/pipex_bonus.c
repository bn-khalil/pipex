/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:28:24 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/06 10:33:28 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

#include <libc.h>

static void	child_process(char *command, char **env, int infd, int outfd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		close_all_unused_fds();
		put_message("Error: fork()\n");
	}
	if (pid == 0)
	{
		dup2(infd, STDIN_FILENO);
		dup2(outfd, STDOUT_FILENO);
		close_all_unused_fds();
		execute_command(command, env);
	}
}

static void	pipeline(int s[], char **av, char **env, int infd)
{
	int	outfd;
	int	fds[2];
	int	prev_in;
	int	i;

	i = s[0];
	prev_in = infd;
	while (i < s[1] - 2)
	{
		piper(fds, prev_in, infd);
		child_process(av[i], env, prev_in, fds[1]);
		ft_closer(prev_in, fds[1], -1, -1);
		prev_in = fds[0];
		i++;
	}
	outfd = ft_opner_file(s[0], av[s[1] - 1]);
	if (outfd < 0)
	{
		close_all_unused_fds();
		put_message("Error: no such file or directory\n");
	}
	child_process(av[i], env, prev_in, outfd);
	close_all_unused_fds();
	while (wait(NULL) > 0)
		;
}

static void	read_and_fill(char **av)
{
	char	*line;
	int		tmpfd;

	tmpfd = ft_opner_file(2, "/tmp/here_doc");
	if (tmpfd < 0)
		put_message("Error: no such file or directory\n");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			break ;
		printf("%zu\n%zu\n", strlen(av[2]), strlen(line));
		if (ft_strncmp(av[2], line, ft_strlen(av[2])) == 0 && \
		ft_strlen(line) - 1 == ft_strlen(av[2]))
			break ;
		write(tmpfd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(tmpfd);
}

static void	here_doc(int s[], char **av, char **env)
{
	int	tmpfd;

	read_and_fill(av);
	tmpfd = ft_opner_file(5, "/tmp/here_doc");
	if (tmpfd < 0)
	{
		unlink("/tmp/here_doc");
		put_message("Error: no such file or directory\n");
	}
	pipeline(s, av, env, tmpfd);
	close(tmpfd);
	unlink("/tmp/here_doc");
}

int	main(int ac, char **av, char **env)
{
	int		infd;
	int		start_end[2];

	start_end[0] = 2;
	start_end[1] = ac;
	if (ac < 5)
		put_message("Error: invalid arguments!\n");
	if (!env)
		put_message("Error: no environment variables!\n");
	if (ft_strncmp("here_doc", av[1], 9) == 0)
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
