# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 17:28:39 by kben-tou          #+#    #+#              #
#    Updated: 2025/01/25 20:02:56 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M = mandatory
U = utils
B = bonus
NAME = pipex

FILS = $(M)/pipex.c \
		$(U)/put_message.c \
		$(U)/ft_split.c \
		$(U)/ft_strnstr.c \
		$(U)/ft_strlen.c \
		$(U)/ft_strjoin.c \
		$(U)/ft_strdup.c \
		$(U)/ft_strchr.c \

CFLAGS =  -Wall -Wextra -Werror

OBJS = 	$(FILS:.c=.o)

all: $(NAME)

%.o: %.c inc/pipex.h
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all