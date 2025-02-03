# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 17:28:39 by kben-tou          #+#    #+#              #
#    Updated: 2025/02/02 22:22:05 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M = mandatory
B = bonus
U = utils
UB = utils_bonus
NAME = pipex
NAME_B = .bonus

FILS = $(M)/pipex.c \
		$(U)/put_message.c \
		$(U)/ft_split.c \
		$(U)/ft_strnstr.c \
		$(U)/ft_strlen.c \
		$(U)/ft_strjoin.c \
		$(U)/ft_strdup.c \
		$(U)/get_next_line.c \
		$(U)/ft_strchr.c \
		$(U)/ft_strncmp.c \
		$(U)/execution.c \

FILS_B = $(B)/pipex_bonus.c \
		$(U)/put_message.c \
		$(U)/ft_split.c \
		$(U)/ft_strnstr.c \
		$(U)/ft_strlen.c \
		$(U)/ft_strjoin.c \
		$(U)/ft_strdup.c \
		$(U)/get_next_line.c \
		$(U)/ft_strchr.c \
		$(U)/ft_strncmp.c \
		$(U)/execution.c \

CFLAGS =  -Wall -Wextra -Werror

OBJS = 	$(FILS:.c=.o)
OBJS_B = $(FILS_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

%.o: %.c inc/pipex.h
	cc $(CFLAGS) -c $< -o $@

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B)
	cc $(CFLAGS) $(OBJS_B) -o $(NAME)
	@touch $(NAME_B)

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all