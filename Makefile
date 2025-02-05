# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 17:28:39 by kben-tou          #+#    #+#              #
#    Updated: 2025/02/05 12:59:48 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M = mandatory
B = bonus
NAME = pipex
NAME_B = .bonus

FILS = $(M)/pipex.c \
		$(M)/put_message.c \
		$(M)/ft_split.c \
		$(M)/ft_strnstr.c \
		$(M)/ft_strlen.c \
		$(M)/ft_strjoin.c \
		$(M)/ft_strdup.c \
		$(M)/get_next_line.c \
		$(M)/ft_strchr.c \
		$(M)/ft_strncmp.c \
		$(M)/execution.c \

FILS_B = $(B)/pipex_bonus.c \
		$(B)/put_message_bonus.c \
		$(B)/ft_split_bonus.c \
		$(B)/ft_strnstr_bonus.c \
		$(B)/ft_strlen_bonus.c \
		$(B)/ft_strjoin_bonus.c \
		$(B)/ft_strdup_bonus.c \
		$(B)/get_next_line_bonus.c \
		$(B)/ft_strchr_bonus.c \
		$(B)/ft_strncmp_bonus.c \
		$(B)/execution_bonus.c \

CFLAGS =  -Wall -Wextra -Werror

OBJS = 	$(FILS:.c=.o)
OBJS_B = $(FILS_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@

$(M)/%.o: $(M)/%.c $(M)/pipex.h
	cc $(CFLAGS) -c $< -o $@

$(B)/%.o: $(B)/%.c $(B)/pipex_bonus.h
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