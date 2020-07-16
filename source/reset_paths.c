/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:45:46 by elindber          #+#    #+#             */
/*   Updated: 2020/07/15 15:21:13 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		room_on_valid_path(t_info *info, int i)
{
	int		y;
	int		t;

	y = 0;
	t = 0;
	while (info->phase == 1 && info->valid_indexes[y][0] != EMPTY)
	{
		while (info->valid_indexes[y][t] != EMPTY)
		{
			if (info->valid_indexes[y][t] == i)
				return (1);
			t++;
		}
		t = 0;
		y++;
	}
	while (info->phase == 2 && info->valid_indexes_2[y][0] != EMPTY)
	{
		while (info->valid_indexes_2[y][t] != EMPTY)
		{
			if (info->valid_indexes_2[y][t] == i)
				return (1);
			t++;
		}
		t = 0;
		y++;
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
