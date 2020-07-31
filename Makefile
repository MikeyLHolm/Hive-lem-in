# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/16 13:21:19 by elindber          #+#    #+#              #
#    Updated: 2020/07/31 12:50:59 by mlindhol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = source/ant_flow.c source/dfs_search.c source/flag_management.c \
	  source/handle_paths.c source/parse_ants.c source/reset_paths.c \
	  source/run_second_and_third_round.c source/sort_rooms.c \
	  source/calculate_moves.c source/divide_ants_to_paths.c \
	  source/free_memory.c source/lem_in.c source/parsing_helpers.c \
	  source/room_sorting_utils.c source/save_path.c source/delete_dead_end.c \
	  source/error_management.c source/get_links.c source/parse.c \
	  source/print.c source/run_path_finding.c source/sort_paths.c

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