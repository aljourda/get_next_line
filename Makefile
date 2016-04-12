# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljourda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 12:05:41 by aljourda          #+#    #+#              #
#    Updated: 2016/01/07 12:05:58 by aljourda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


all:
	#make -C libft/ fclean
	make -C libft/
	clang -Wall -Wextra -I libft/includes -o get_next_line.o -c get_next_line.c
	clang  -Wall -Wextra -I libft/includes -o main.o -c main.c
	clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft