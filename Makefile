# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elindber <elindber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/16 13:21:19 by elindber          #+#    #+#              #
#    Updated: 2020/07/13 14:48:50 by elindber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = source/*.c

LIBFT = ./libftprintf/libftprintf.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@ make -C libftprintf/ re
	@ gcc $(FLAGS) -o $(NAME) $(SRC) $(LIBFT)
	@ echo "Compiled"

clean:
	@ make -C libftprintf/ clean
	@ /bin/rm -f *.o

fclean: clean
	@ make -C libftprintf/ fclean
	@ /bin/rm -f $(NAME)
	@ echo "Executable and libraries removed"

re : fclean all