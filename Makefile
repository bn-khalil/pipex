# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 17:28:39 by kben-tou          #+#    #+#              #
#    Updated: 2025/01/29 13:20:02 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M = mandatory
U = utils
B = bonus
NAME = pipex
NAME_B = pipex_bonus

FILS = $(M)/pipex.c \
		$(U)/put_message.c \
		$(U)/ft_split.c \
		$(U)/ft_strnstr.c \
		$(U)/ft_strlen.c \
		$(U)/ft_strjoin.c \
		$(U)/ft_strdup.c \
		$(U)/ft_strchr.c \
		$(U)/ft_strncmp.c \
		$(U)/execution.c \
		$(U)/get_next_line.c \

FILS_B = $(B)/pipex_bonus.c \
		$(U)/put_message.c \
		$(U)/ft_split.c \
		$(U)/ft_strnstr.c \
		$(U)/ft_strlen.c \
		$(U)/ft_strjoin.c \
		$(U)/ft_strdup.c \
		$(U)/ft_strchr.c \
		$(U)/ft_strncmp.c \
		$(U)/execution.c \
		$(U)/get_next_line.c \

CFLAGS =  -Wall -Wextra -Werror

OBJS = 	$(FILS:.c=.o)
OBJS_B = $(FILS_B:.c=.o)

all: $(NAME)

%.o: %.c inc/pipex.h
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

bonus: $(NAME) $(NAME_B)

$(NAME_B): $(OBJS_B)
	cc $(CFLAGS) $(OBJS_B) -o $@

clean: 
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all