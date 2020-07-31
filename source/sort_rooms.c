/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:34:22 by elindber          #+#    #+#             */
/*   Updated: 2020/07/31 12:35:58 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	split_link_string(t_info *info, int index)
{
	info->rooms[index]->links =
	ft_strsplit(info->rooms[index]->link_string, ' ');
	free(info->rooms[index]->link_string);
	if (info->rooms[index]->start_or_end != 0)
	{
		if (info->rooms[index]->start_or_end == 1)
			info->start_index = index;
		else
			info->end_index = index;
	}
}

void	first_from_index(t_info *info, int i)
{
	int		first;
	int		placement;

	first = i + 1;
	placement = i;
	while (info->rooms[i] != NULL)
	{
		if (ft_strcmp(info->rooms[i]->name, info->rooms[first]->name) < 0)
			first = i;
		if (info->rooms[++i] != NULL)
		{
			if (info->rooms[placement]->x == info->rooms[i]->x
			&& info->rooms[placement]->y == info->rooms[i]->y)
				exit_error(ERR_ROOM_DUP_COORD, info);
			else if (!(ft_strcmp(info->rooms[placement]->name,
			info->rooms[i]->name)))
				exit_error(ERR_ROOM_DUP_NAME, info);
		}
	}
	swap_rooms(info, first, placement);
	if (info->rooms[placement + 1] != NULL)
		split_link_string(info, placement);
}

void	malloc_for_valid_indexes(t_info *info, int i, int x)
{
	if (!(info->valid_indexes =
	(int**)malloc(sizeof(int*) * info->max_paths + 1))
	|| !(info->valid_indexes_2 =
	(int**)malloc(sizeof(int*) * info->max_paths + 1))
	|| !(info->valid_paths =
	(char**)malloc(sizeof(char*) * info->max_paths + 1))
	|| !(info->valid_paths_2 =
	(char**)malloc(sizeof(char*) * info->max_paths + 1)))
		exit_error(ERR_MALLOC, info);
	while (i < info->max_paths + 1)
	{
		if (!(info->valid_indexes[i] = (int*)malloc(sizeof(int) * 513))
		|| !(info->valid_indexes_2[i] = (int*)malloc(sizeof(int) * 513)))
			exit_error(ERR_MALLOC, info);
		while (x < 513)
		{
			info->valid_indexes[i][x] = EMPTY;
			info->valid_indexes_2[i][x] = EMPTY;
			x++;
		}
		x = 0;
		i++;
	}
}

/*
**	Sorts rooms in ASCII. Quickens searching for a room with binary search.
*/

void	sort_rooms(t_info *info)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (info->rooms[i + 1] != NULL)
	{
		first_from_index(info, i);
		i++;
	}
	split_link_string(info, i);
	i = 0;
	while (info->rooms[info->start_index]->links[i] != NULL)
		i++;
	while (info->rooms[info->end_index]->links[x] != NULL)
		x++;
	info->max_paths = i < x ? i : x;
	malloc_for_valid_indexes(info, 0, 0);
}
