# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elindber <elindber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 16:24:48 by elindber          #+#    #+#              #
#    Updated: 2020/06/10 10:36:05 by elindber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = srcs/ft_printf.c srcs/minwth_print.c srcs/print_c.c srcs/print_f.c \
	  srcs/print_p.c srcs/print_s.c srcs/print_x.c srcs/scan_tags.c \
	  srcs/imaxtoa.c srcs/number_cast.c srcs/print_d.c srcs/print_o.c \
	  srcs/print_percent.c srcs/print_u.c srcs/put_zeros.c \
	  srcs/set_tags_and_print.c srcs/get_next_line.c

OBJ = ft_printf.o minwth_print.o print_c.o print_f.o print_p.o print_s.o \
	  print_x.o scan_tags.o imaxtoa.o number_cast.o print_d.o print_o.o \
	  print_percent.o print_u.o put_zeros.o set_tags_and_print.o \
	  get_next_line.o

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME):
	@ make -C libft/ fclean && make -C libft/
	@ cp $(LIBFT) $(NAME)
	@ gcc -Wall -Wextra -Werror -c $(SRC)
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)
	@ echo "libftprintf.a done"

clean:
	@ /bin/rm -f *.o
	@ make -C libft/ clean
	@ echo "printf: object files removed"

fclean: clean
	@ /bin/rm -f $(NAME)
	@ make -C libft/ fclean
	@ /bin/rm -f a.out
	@ echo "executables and a.out removed"

re: fclean all

run: $(NAME)
	@ gcc $(NAME) main.c
	@ /bin/rm -f *.o
	@ make -C libft/ clean
	@ ./a.out
