/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:45:46 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 18:19:49 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	reset_tmp_stacks(t_info *info)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (i < 513)
	{
		info->tmp_string[i] = EMPTY;
		info->check_rooms[i] = EMPTY;
		i++;
	}
	i = 0;
	while (y < info->link_amnt)
	{
		while (i < 513)
		{
			info->index_stack[y][i] = EMPTY;
			i++;
		}
		i = 0;
		y++;
	}
}

int		room_on_valid_path(t_info *info, int i)
{
	int		y;
	int		t;

	y = -1;
	t = -1;
	while (info->phase == 1 && info->valid_indexes[++y][0] != EMPTY)
	{
		while (info->valid_indexes[y][++t] != EMPTY)
		{
			if (info->valid_indexes[y][t] == i)
				return (1);
		}
		t = -1;
	}
	while (info->phase == 2 && info->valid_indexes_2[++y][0] != EMPTY)
	{
		while (info->valid_indexes_2[y][++t] != EMPTY)
		{
			if (info->valid_indexes_2[y][t] == i)
				return (1);
		}
		t = -1;
	}
	return (0);
}

void	reset_rooms(t_info *info)
{
	int		i;

	i = 0;
	info->level = 1;
	while (info->rooms[i] != NULL)
	{
		if (room_on_valid_path(info, i) && i != info->end_index)
			info->rooms[i]->visited = 2;
		else
			info->rooms[i]->visited = 0;
		i++;
	}
}
