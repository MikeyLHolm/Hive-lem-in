/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:33:19 by elindber          #+#    #+#             */
/*   Updated: 2020/07/31 14:19:36 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		reset_valid_indexes_2(t_info *info)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (y < info->max_paths + 1)
	{
		while (i < 513)
		{
			if (info->valid_indexes_2[y][i] > 0)
			{
				info->rooms[info->valid_indexes_2[y][i]]->length_2 = 0;
				info->rooms[info->valid_indexes_2[y][i]]->cost_2 = 0;
				info->rooms[info->valid_indexes_2[y][i]]->path_2 = -1;
			}
			info->valid_indexes_2[y][i] = EMPTY;
			i++;
		}
		i = 0;
		y++;
	}
	info->path_n_2 = 0;
}

void		path_set_insert(t_info *info, int i, int y)
{
	info->rooms[info->valid_indexes[y][i]]->length =
	info->rooms[info->valid_indexes[y][i]]->length_2;
	info->rooms[info->valid_indexes[y][i]]->cost =
	info->rooms[info->valid_indexes[y][i]]->cost_2;
	info->rooms[info->valid_indexes[y][i]]->path =
	info->rooms[info->valid_indexes[y][i]]->path_2;
	info->rooms[info->valid_indexes[y][i]]->path_2 = -1;
}

void		change_path_sets(t_info *info)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (y < info->max_paths + 1)
	{
		while (i < 513)
		{
			info->valid_indexes[y][i] = info->valid_indexes_2[y][i];
			if (info->valid_indexes[y][i] != EMPTY)
				path_set_insert(info, i, y);
			info->valid_indexes_2[y][i] = EMPTY;
			i++;
		}
		i = 0;
		y++;
	}
	info->path_n_1 = info->path_n_2;
	info->last_found_used = info->last_found_used_2;
	info->last_found_used_2 = 1;
	info->path_n_2 = 0;
}

int			calculate_more(t_info *info, int i, int rooms, int set)
{
	int		moves;
	int		d;

	if (set == 1)
	{
		while (++i < info->path_n_1)
			rooms += info->rooms[info->valid_indexes[i][0]]->length;
		rooms -= info->last_found_used == 1 ? 0 :
		info->rooms[info->valid_indexes[i - 1][0]]->length;
		d = info->last_found_used == 1 ? info->path_n_1 : info->path_n_1 - 1;
		d = d == 0 ? 1 : d;
		moves = ((rooms + info->ants) / d) + ((rooms + info->ants) % d ? 1 : 0);
	}
	else
	{
		while (++i < info->path_n_2)
			rooms += info->rooms[info->valid_indexes_2[i][0]]->length_2;
		rooms -= info->last_found_used_2 == 1 ? 0 :
		info->rooms[info->valid_indexes_2[i - 1][0]]->length_2;
		d = info->last_found_used_2 == 1 ? info->path_n_2 : info->path_n_2 - 1;
		d = d == 0 ? 1 : d;
		moves = ((rooms + info->ants) / d) + ((rooms + info->ants) % d ? 1 : 0);
	}
	return (moves);
}

void		calculate_moves(t_info *info)
{
	int		moves;
	int		cmp;

	if (info->path_n_2 < 1)
	{
		reset_valid_indexes_2(info);
		return ;
	}
	moves = calculate_more(info, -1, 0, 1);
	cmp = calculate_more(info, -1, 0, 2);
	if (info->flag_storage & VERBOSE)
		ft_printf("%d  %d\n```````\n", moves, cmp);
	if (moves <= info->required + 2 || cmp <= info->required + 2)
		info->accurate = 1;
	if (cmp < moves)
	{
		if (info->flag_storage & VERBOSE)
			ft_printf("><><><><C H A N G I N G  P A T H  S E T><><><><><\n\n");
		change_path_sets(info);
	}
	else
		reset_valid_indexes_2(info);
}
