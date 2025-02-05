/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:08:06 by kben-tou          #+#    #+#             */
/*   Updated: 2025/02/05 15:37:17 by kben-tou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

void	put_message(char *msg);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	ft_free_2d(char **content);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*get_path(char **env);
char	*get_path_command(char *command, char **env, char **cmd_flags);
char	*parse_command(char *command);
void	execute_command(char *command, char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
void	ft_closer(int read_end, int write_end, int infd, int outfd);
void	put_and_free(char *msg, char **content);
void	piper(int fds[], int prev_in, int infd);
int		ft_opner_file(int status, char *filename);
void	close_all_unused_fds(void);
int		ft_isalpha(int c);

#endif
