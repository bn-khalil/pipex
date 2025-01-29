#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
void    put_message(char *msg);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void    ft_free_2d(char **content);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char    *get_path(char **env);
char    *get_path_command(char *command, char **env, char **cmd_flags);
char    *parse_command(char *command);
void    execute_command(char *command, char **env);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
void    ft_closer(int read_end , int write_end, int infd, int outfd);
void    put_and_free(char *msg, char **content);

#endif