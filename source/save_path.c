/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:01:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/21 16:55:34 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	reset_tmp_stacks(t_info *info)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (info->tmp_string[i] != EMPTY)
		info->tmp_string[i++] = EMPTY;
	i = 0;
	while (info->check_rooms[i] != EMPTY)
		info->check_rooms[i++] = EMPTY;
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

int		check_end(t_info *info)
{
	int		y;

	y = 0;
	if (info->path_amount_1 == info->max_paths)
	{
		info->path_saved = 2;
		return (1);
	}
	while (info->index_stack[y][0] != EMPTY)
	{
		if (info->index_stack[y][0] != LOCKED)
			return (0);
		y++;
	}
	info->path_saved = 2;
	return (0);
}

int		enough_paths(t_info *info, int path_index)
{
	int		cmp_length;
	int		sum;
	int		i;

	if ((info->phase == 1 && info->path_amount_1 == info->max_paths)
	|| (info->phase == 2 && info->path_amount_2 == info->max_paths))
		return (1);
	else if ((info->phase == 1 && info->path_amount_1 == 1)
	|| (info->phase == 2 && info->path_amount_2 == 1))
		return (0);
	cmp_length = info->phase == 1 ? info->rooms[info->valid_indexes[path_index][0]]->length
	: info->rooms[info->valid_indexes_2[path_index][0]]->length_2;
	sum = 0;
	i = 0;
	while (i < path_index)
	{
		sum += info->phase == 1 ? (cmp_length - info->rooms[info->valid_indexes[i][0]]->length)
		: (cmp_length - info->rooms[info->valid_indexes_2[i][0]]->length_2);
		i++;
	}
	return (sum >= info->ants);
}

void	delete_duplicates(t_info *info, int *path)
{
	int		i;
	int		t;
	int		u;

	i = 0;
	t = 0;
	u = 0;
	while (path[i] != EMPTY)
	{
		while (info->index_stack[t][0] != EMPTY)
		{
			while (info->index_stack[t][u] != EMPTY)
			{
				if (info->index_stack[t][u] == path[i])
				{
					info->index_stack[t][0] = LOCKED;
					u = 126;
				}
				u++;
			}
			u = 0;
			t++;
		}
		i++;
	}
}

void	save_path_to_string(t_info *info)
{
	char	*add;
	char	*tmp;
	int		i;
	int		u;

	i = 0;
	u = info->phase == 1 ? info->path_amount_1 : info->path_amount_2;
	while (info->phase == 1 && info->valid_indexes[u][i] != EMPTY)
	{
		add = ft_strjoin(info->rooms[info->valid_indexes[u][i]]->name, " ");
		tmp = ft_strjoin(info->valid_paths[u], add);
		ft_strdel(&info->valid_paths[u]);
		info->valid_paths[u] = ft_strdup(tmp);
		ft_strdel(&add);
		ft_strdel(&tmp);
		i++;
	}
	while (info->phase == 2 && info->valid_indexes_2[u][i] != EMPTY)
	{
		add = ft_strjoin(info->rooms[info->valid_indexes_2[u][i]]->name, " ");
		tmp = ft_strjoin(info->valid_paths_2[u], add);
		ft_strdel(&info->valid_paths_2[u]);
		info->valid_paths_2[u] = ft_strdup(tmp);
		ft_strdel(&add);
		ft_strdel(&tmp);
		i++;
	}
}

void	save_path(t_info *info, int path_i)
{
	int		i;
	int		u;

	u = info->phase == 1 ? info->path_amount_1 : info->path_amount_2;
	i = 0;
	if (info->phase == 1)
		info->valid_paths[u] = ft_strnew(0);
	else
		info->valid_paths_2[u] = ft_strnew(0);
	while (info->index_stack[path_i][i] != EMPTY)
	{
		if (info->phase == 1)
		{
			info->valid_indexes[info->path_amount_1][i] = info->index_stack[path_i][i];
			if (info->index_stack[path_i][i] != info->end_index)
			{
				info->rooms[info->index_stack[path_i][i]]->flow = 1;
				info->rooms[info->index_stack[path_i][i]]->path = info->path_amount_1;
			}
		}
		else
		{
			info->valid_indexes_2[info->path_amount_2][i] = info->index_stack[path_i][i];
			if (info->index_stack[path_i][i] != info->end_index)
			{
				info->rooms[info->index_stack[path_i][i]]->flow += 2;
				info->rooms[info->index_stack[path_i][i]]->path_2 = info->path_amount_2;
			}
		}
		i++;
	}
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
	if (!(info->rooms[info->index_stack[path_i][0]]->ant_queue = (int*)malloc(sizeof(int) * info->ants + 1))
	|| !(info->rooms[info->index_stack[path_i][0]]->ant_queue_2 = (int*)malloc(sizeof(int) * info->ants + 1)))
		exit_error(ERR_MALLOC, info);
	i = 0;
	while (i < info->ants + 1)
	{
		info->rooms[info->index_stack[path_i][0]]->ant_queue[i] = 0;
		info->rooms[info->index_stack[path_i][0]]->ant_queue_2[i] = 0;
		i++;
	}
	i = 0;
	save_path_to_string(info);
//	if (info->phase == 1)
//		ft_printf("\nS A V I N G (first round):\n[%s]\n", info->valid_paths[info->path_amount_1]);
//	else
//		ft_printf("\nS A V I N G (second round):\n[%s]\n", info->valid_paths_2[info->path_amount_2]);
	info->phase == 1 ? info->path_amount_1++ : info->path_amount_2++;
	info->path_saved = 1;
	//	"check if further paths are needed function" --> if no more paths needed change info->path_saved = 2;
	if ((info->phase == 1 && enough_paths(info, info->path_amount_1 - 1)) 
	|| (info->phase == 2 && enough_paths(info, info->path_amount_2 - 1)))
	{
		info->path_saved = 2;
		return ;
	}
	reset_rooms(info);
	reset_tmp_stacks(info);
}
