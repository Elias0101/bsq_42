# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bnigellu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/20 22:00:36 by bnigellu          #+#    #+#              #
#    Updated: 2019/03/20 22:37:47 by bnigellu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

FLAGS = gcc -Wall -Werror -Wextra

HEADER = header.h

all:
	@$(FLAGS) -o $(NAME) *.c

clean:
	@/bin/rm -f *.o
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean all
