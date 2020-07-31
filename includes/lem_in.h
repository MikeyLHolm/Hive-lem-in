/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:42:05 by elindber          #+#    #+#             */
/*   Updated: 2020/07/31 16:04:30 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/get_next_line.h"
# include "../libftprintf/libft/libft.h"

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

/*
**	Error Management
*/

# define ERR_ANTS			"Error: Ant amount must be between 1 and 999999"
# define ERR_BAD_LINK		"Error: Invalid link"
# define ERR_DUP_LINK		"Error: Duplicate link found"
# define ERR_MALLOC			"Error: Failed to Malloc!"
# define ERR_NO_LINK		"Error: No links found"
# define ERR_NO_MAP			"Error: No map found"
# define ERR_NO_PATH		"Error: No path found!"
# define ERR_ROOM_ARGS_FEW	"Error: Too few room arguments"
# define ERR_ROOM_ARGS_MANY	"Error: Too many room arguments"
# define ERR_ROOM_DUP_COORD	"Error: Duplicate room coordinates found!"
# define ERR_ROOM_DUP_NAME	"Error: Duplicate room names found!"
# define ERR_ROOM_M_END		"Error: Multiple ends found!"
# define ERR_ROOM_M_START	"Error: Multiple starts found!"
# define ERR_ROOM_NAME_DASH	"Error: Room name including '-'"
# define ERR_ROOM_NO_END	"Error: No end room!"
# define ERR_ROOM_NO_ROOMS	"Error: No rooms found!"
# define ERR_ROOM_NO_START	"Error: No start room!"
# define ERR_ROOM_STARTS_L	"Error: Room name starting with 'L'"
# define ERR_USAGE			"USAGE: ./lem-in < [file]"

/*
**	Other defined values
*/

# define EMPTY -1

/*
**	Define flags
*/

# define ANTS		1
# define ERROR		2
# define HELP		4
# define LEAKS		8
# define LINES		16
# define PATHS		32
# define VERBOSE	64

/*
**	Define colors for printing.
*/

# define RED 			"\033[0;31m"
# define BOLD_RED 		"\033[1;31m"
# define GREEN 			"\033[0;32m"
# define BOLD_GREEN 	"\033[1;32m"
# define YELLOW 		"\033[0;33m"
# define BOLD_YELLOW 	"\033[01;33m"
# define BLUE 			"\033[0;34m"
# define BOLD_BLUE 		"\033[1;34m"
# define MAGENTA 		"\033[0;35m"
# define BOLD_MAGENTA 	"\033[1;35m"
# define CYAN 			"\033[0;36m"
# define BOLD_CYAN 		"\033[1;36m"
# define WHITE			"\033[0:37m"
# define RESET 			"\033[0m"

typedef struct			s_output
{
	char				*line;
	struct s_output		*next;
}						t_output;

typedef struct			s_room
{
	char				*link_string;
	char				**links;
	char				*name;
	int					ant_id;
	int					*ant_queue;
	int					*ant_queue_2;
	int					ants;
	int					ants_2;
	int					flow;
	int					cost;
	int					cost_2;
	int					length;
	int					length_2;
	int					level;
	int					path;
	int					path_2;
	int					start_or_end;
	int					visited;
	int					x;
	int					y;
}						t_room;

typedef struct			s_info
{
	char				*end;
	char				**rooms_to_check;
	char				*start;
	char				**valid_paths;
	char				**valid_paths_2;
	int					ants;
	int					ants_at_end;
	int					ants_at_start;
	int					check_rooms[513];
	int					lvl_1_rooms[513];
	int					end_index;
	int					flag_storage;
	int					**index_stack;
	int					level;
	int					lines;
	int					link_amnt;
	int					max_paths;
	int					path_n_1;
	int					path_n_2;
	int					path_saved;
	int					phase;
	int					round;
	int					room_amnt;
	int					start_index;
	int					tmp_string[513];
	int					fd;
	int					start_end_link;
	int					last_found_used;
	int					last_found_used_2;
	int					required;
	int					accurate;
	int					**valid_indexes;
	int					**valid_indexes_2;
	t_room				**rooms;
}						t_info;

/*
** Misc functions
*/

int						ft_isint(char *str);
void					reset_tmp_stacks(t_info *info);
void					start_over_or_continue(t_info *info, int index);

/*
**	Link related functions
*/

void					get_links(t_info *info);
void					get_links_for_start(t_info *info, int i, int s, int t);
void					delete_dead_end(t_info *info, int dead_end);

/*
**	Parsing functions
*/

void					parse_ants(t_info *info, t_output *output);
void					parse_flags(int ac, char **av, t_info *info);
void					parse_map(t_output *output, t_info *info);
void					init_room_info(t_info *info, int i);
void					get_required_lines(t_info *info, char *line);
int						validate_command(t_info *info, char *line);

/*
**	Parsing helpers
*/

void					add_new_link(t_info *info, int i, char *room);
void					add_links_for_rooms
(t_info *info, char *room1, char *room2);
void					room_error_check(t_info *info, char **room_data);

/*
**	Printing functions
*/

void					help_print(void);
void					print_ant(char *ant, t_info *info, int i, char *room);
void					print_paths(t_info *info);

/*
**	Path related functions
*/

void					add_to_path(t_info *info, int s, int i, int y);
void					calculate_moves(t_info *info);
void					second_round(t_info *info);
void					third_round(t_info *info);
void					dfs_search(t_info *info, int i);
void					find_paths(t_info *info, int i, int j, int l);
int						last_on_path(int *path);
void					save_path(t_info *info, int path_i, int i);
void					search_from_room(t_info *info);
void					sort_paths(t_info *info);

/*
**	Room related functions
*/

void					copy_check_rooms(t_info *info);
int						find_a_room(t_info *info, char *to_find);
void					reorder_check_rooms(t_info *info);
void					reset_rooms(t_info *info);
void					set_visited(t_info *info, int s, int l);
void					sort_rooms(t_info *info);
void					swap_rooms(t_info *info, int a, int b);

/*
**	Ant turns functions
*/

void					divide_to_paths(t_info *info, int i, int tab, int cmp);
void					ant_flow(t_info *info);

/*
**	Memory allocation freeage
*/

void					free_2d_array(char **arr);
void					lst_free(t_output *op);

/*
**	Error management functions
*/

void					exit_error(const char *str, t_info *info);
void					exit_error_no_info(const char *str);

#endif
