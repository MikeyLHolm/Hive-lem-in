/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:01:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/29 16:30:15 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		enough_paths(t_info *info, int path_index, int sum, int i)
{
	int		cmp_length;

	if ((info->phase == 1 && info->path_n_1 == info->max_paths)
	|| (info->phase == 2 && info->path_n_2 == info->max_paths))
		return (1);
	else if ((info->phase == 1 && info->path_n_1 == 1)
	|| (info->phase == 2 && info->path_n_2 == 1))
		return (0);
	cmp_length = info->phase == 1 ?
	info->rooms[info->valid_indexes[path_index][0]]->length :
	info->rooms[info->valid_indexes_2[path_index][0]]->length_2;
	while (i < path_index)
	{
		sum += info->phase == 1 ?
		(cmp_length - info->rooms[info->valid_indexes[i][0]]->length) :
		(cmp_length - info->rooms[info->valid_indexes_2[i][0]]->length_2);
		i++;
	}
	if (info->phase == 1)
		info->last_found_used = sum >= info->ants ? 0 : 1;
	else
		info->last_found_used_2 = sum >= info->ants ? 0 : 1;
	return (sum >= info->ants);
}

void	copy_path_to_valid_indexes(t_info *info, int path_i, int i)
{
	if (info->phase == 1)
	{
		info->valid_indexes[info->path_n_1][i] = info->index_stack[path_i][i];
		if (info->index_stack[path_i][i] != info->end_index)
		{
			info->rooms[info->index_stack[path_i][i]]->flow = 1;
			info->rooms[info->index_stack[path_i][i]]->path = info->path_n_1;
		}
	}
	else
	{
		info->valid_indexes_2[info->path_n_2][i] = info->index_stack[path_i][i];
		if (info->index_stack[path_i][i] != info->end_index)
		{
			info->rooms[info->index_stack[path_i][i]]->flow += 2;
			info->rooms[info->index_stack[path_i][i]]->path_2 = info->path_n_2;
		}
	}
}

void	set_lengths(t_info *info, int path_i, int i)
{
	if (info->phase == 1)
	{
		info->rooms[info->index_stack[path_i][0]]->length = i - 1;
		info->rooms[info->index_stack[path_i][0]]->cost = i - 1;
	}
	else
	{
		info->rooms[info->index_stack[path_i][0]]->length_2 = i - 1;
		info->rooms[info->index_stack[path_i][0]]->cost_2 = i - 1;
	}
	if (!(info->rooms[info->index_stack[path_i][0]]->ant_queue)
	&& !(info->rooms[info->index_stack[path_i][0]]->ant_queue =
	(int*)malloc(sizeof(int) * info->ants + 1)))
		exit_error(ERR_MALLOC, info);
	i = 0;
	while (i < info->ants + 1)
	{
		info->rooms[info->index_stack[path_i][0]]->ant_queue[i] = 0;
		i++;
	}
}

void	save_path(t_info *info, int path_i, int i)
{
	if (info->phase == 2 && info->last_found_used_2 == 0)
		return ;
	while (info->index_stack[path_i][i] != EMPTY)
	{
		copy_path_to_valid_indexes(info, path_i, i);
		i++;
	}
	set_lengths(info, path_i, i);
	i = 0;
	info->phase == 1 ? info->path_n_1++ : info->path_n_2++;
	info->path_saved = 1;
	sort_paths(info);
	if ((info->phase == 1 && enough_paths(info, info->path_n_1 - 1, 0, 0))
	|| (info->phase == 2 && enough_paths(info, info->path_n_2 - 1, 0, 0)))
	{
		info->path_saved = 2;
		return ;
	}
	reset_rooms(info);
	reset_tmp_stacks(info);
}
