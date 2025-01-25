#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <libc.h>

void    put_message(char *msg, int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void    ft_free_2d(char **content);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);

#endif