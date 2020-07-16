/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_turns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:27:35 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/15 13:46:17 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				to_path_or_not_to_path(t_info *lem_in, char *path)
{
	int			calc;
	int			i;

	calc = 0;
	i = -1;
	while (lem_in->valid_paths[++i] != path)
	{
		// calc += path - lem_in->valid_paths[i]->length;
		//move to next path

	}
	return (calc);
}

static void		ant_start_to_path(t_info *lem_in, char *path)
{
	path[0] += 0;
	// if (next room = end)
	// {
	// 	--lem_in->ants_start;
	// 	++lem_in->ants_end;
	// 	locations?
	// } should be if else with below.
	// else
	--lem_in->ants_at_start;
	// all location related here:
		// lem_in->ant->room = path[0]->room->name
		// path[0]->room->ant_number = lem_in->ant->number;
}

/*
**	Check every path if ants should be inserted.
*/


static void		ants_to_paths(t_info *lem_in, int n_of_paths)
{
	int			i;
	int			j;
	char		**path;

	i = 0;
	j = 0;
	ft_printf("test1\n");
	path = ft_strsplit(lem_in->valid_paths[i], ' ');
	// check if path works.
	ft_printf("test2\n");
	while (path[i])
	{
		ft_printf("%s\n", path[i]);
		i++;
	}
	i = -1;
	ft_printf("test3\n");
	while (++i < n_of_paths)
	{
		path = ft_strsplit(lem_in->valid_paths[i], ' ');

		if (lem_in->ants > to_path_or_not_to_path(lem_in, *path))
		{
			write(1, "Hello\n", 6);
			ant_start_to_path(lem_in, *path);
		}
		//free_2d_array(path);
		free(path);
	}
}

// static void		move_single_path(t_info *lem_in, char *path)
// {
// 	int			room_i;

// 	room_i = path->length;
// 	while (--room_i >= 0)
// 	{
// 		if (isempty(path[room_i]))
// 			continue ;
// 		// found ant from the room, what next?
// 			// if last node of the path.
// 				// ++lem_in->ants_end;
// 				// clear room+update ant position?
// 			// else
// 				// ant position changes from path[room_i] to path[room_i + 1]
// 				// path[room_i] clear
// 	}
// }

// static void		move_existing_ants(t_info *lem_in, int n_of_paths)
// {

// 	while (--n_of_paths >= 0)
// 	{
// 		move_single_path(lem_in);
// 	}
// }

void			take_turns(t_info *info)
{
	int			count;

	count = 0;
	info->ants_at_start = info->ants;
	//ft_printf("path: %s\n", info->valid_paths[0]);
//	ft_printf("path[0] length: %d", info->rooms[info->valid_indexes[0][0]]->length);
	// TURNS LOOP
	while (info->ants || info->ants != info->ants_at_end)
	{
	//	ft_printf("test a\n");
		if (info->ants != info->ants_at_start)
			//move_existing_ants(info, info->path_amount);
	//	ft_printf("test b\n");
		if (info->ants_at_start > 0)
		{
		//	ft_printf("test c\n");
			ants_to_paths(info, info->path_amount_1);
		}
	//	ft_printf("test d\n");
	//	print_locations(info);
	//	lst_free(info);
		++count;
	}
	ft_printf("\n\n*** LINES COUNT = %d ***\n\n", count);
}
