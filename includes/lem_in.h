/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:42:05 by elindber          #+#    #+#             */
/*   Updated: 2020/07/21 16:28:06 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/get_next_line.h"
# include "../libftprintf/libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h> //debug include

/*
**	Error Management
**
**	possible adds:
**					-Room name with # or L.
**					-more specific ant errors
**					-Locations: (L-1-3), (L11 with 10 ant map), (L0-3), (L1-X)
*/

# define ERR_ANTS			"Error: Ant amount must be between 1 and 999999"
# define ERR_BAD_LINK		"Error: Link to non-existing room detected"
# define ERR_DUP_LINK		"Error: Duplicate link found"
# define ERR_NO_LINK		"Error: No links found"
# define ERR_NO_PATH		"Error: No path found!"
# define ERR_OPEN			"Error: Failed to open!"
# define ERR_MALLOC			"Error: Failed to Malloc!"
# define ERR_USAGE			"USAGE: ./lem-in < [file]"
# define ERR_NO_EL			"Error: No empty line between links and locations"
# define ERR_PARSE_V2		"Error: !Parse_v2"
# define ERR_ROOM_STARTS_L	"Error: Room name starting with 'L'"
# define ERR_ROOM_STARTS_SH	"Error: Room name starting with '#'"
# define ERR_ROOM_NAME_DASH	"Error: Room name including '-'"
# define ERR_ROOM_ARGS_FEW	"Error: Too few room arguments"
# define ERR_ROOM_ARGS_MANY	"Error: Too many room arguments"
# define ERR_ROOM_DUP_COORD	"Error: Duplicate room coordinates found!"
# define ERR_ROOM_M_END		"Error: Multiple ends found!"
# define ERR_ROOM_M_START	"Error: Multiple starts found!"
# define ERR_ROOM_DUP_NAME	"Error: Duplicate room names found!"
# define ERR_ROOM_NO_END	"Error: No end room!"
# define ERR_ROOM_NO_ROOMS	"Error: No rooms found!"
# define ERR_ROOM_NO_START	"Error: No start room!"

/*
**	Other defined values
*/

# define EMPTY -1
# define LOCKED -2

/*
**	Enums for boolean
*/

typedef enum
{
		FALSE,
		TRUE,
}		t_bool;

typedef struct			s_flags
{
	int					ants;
	int					error;
	int					help;
	int					lines;
	int					paths;
	int					verbose;
}						t_flags;

typedef struct			s_output
{
	char				*line;
	struct s_output		*next;
}						t_output;



typedef struct			s_room
{
	char				**links;
	char				*link_string;
	char				*name;
	int					*ant_queue;
	int					*ant_queue_2;
	int					start_or_end;
	int					visited;
	int					path;
	int					path_2;
	int					level;
	int					length;
	int					length_2;
	int					cost;
	int					cost_2;
	int					ants;
	int					ants_2;
	int					ant_id;
	int					flow;
	int					y;
	int					x;
}						t_room;

typedef struct			s_route
{
	char				*name;
	int					ants;
	int					visited;
	int					path;
	int					start_or_end;
	int					level;
}						t_route;

typedef struct			s_ant
{
	int					number;
	int					path;
	char				*room;
}						t_ant;

typedef struct			s_location
{
	int					ant_number;
	t_room				*room;
	struct s_location	*next;
	struct s_location	*previous;
}						t_location;

typedef struct			s_info
{
	char				*start;
	char				*end;
	int					level;
	int					ants;
	int					ants_at_start;
	int					ants_at_end;
	int					path_amount_1;
	int					path_amount_2;
	int					max_paths;
	int					path_saved;
	int					phase;
	int					link_amnt;
	int					room_amnt;
	int					path_stack;
	int					start_index;
	int					end_index;
	int					**index_stack;
	int					**valid_indexes;
	int					**valid_indexes_2;
	int					check_rooms[513];
	int					lines;
	int					usage;
	char				**map;
	char				***links;
	char				**paths; // can be removed later
	char				**valid_paths;
	char				**valid_paths_2;
	char				**rooms_to_check;
	int					tmp_string[513];
	t_ant				*ant;
	t_flags				*flags;
	t_location			*location;
	t_room				**rooms;
	t_room				***route;
	int					tmpfd;
}						t_info;

typedef struct			s_link
{
	t_room				*room1;
	t_room				*room2;
	struct s_link		*next;
}						t_link;

typedef struct			s_path
{
	char				**rooms;
	int					length;
	int					ants_on_path;
	struct s_path		*next;
}						t_path;

/*
** Functions
*/

int						parse_v2(t_output *output, t_info *info);
int						last_on_path(int *path);
void					get_links(t_info *info);
int						get_links_for_start(t_info *info);
void					save_path(t_info *info, int path_i);
void					exit_error(const char *str, t_info *info);
void					exit_error_no_info(const char *str);
void					free_2d_array(char **arr);
void					find_paths(t_info *info);
void					add_to_path(t_info *info, int s, int i, int y);
void					sort_rooms(t_info *info);
int						find_a_room(t_info *info, char *to_find);
void					print_paths(t_info *info);
void					reset_rooms(t_info *info);
void					reset_tmp_stacks(t_info *info);

void					parse_ants(t_info *info, t_output *output);
int						ft_isint(char *str);
void					parse_flags(int ac, char **av, t_info *info);

/*
**	Ant turns functions
*/

void					lst_free(t_output *op);
void					print_locations(t_info *info);
void					take_turns(t_info *info);
void					ant_flow(t_info *info);
void					print_turns_2(t_info *info);

#endif
