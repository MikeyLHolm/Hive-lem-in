/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:30:23 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 17:24:23 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	swap_paths(t_info *info, int top, int stack)
{
	int		i;
	int		swap[513];

	i = -1;
	while (++i < 513)
		swap[i] = EMPTY;
	i = -1;
	while (stack == 1 && ++i < 513)
		swap[i] = info->valid_indexes[top][i];
	i = -1;
	while (stack == 1 && ++i < 513)
		info->valid_indexes[top][i] = info->valid_indexes[top + 1][i];
	i = -1;
	while (stack == 1 && ++i < 513)
		info->valid_indexes[top + 1][i] = swap[i];
	i = -1;
	while (stack == 2 && ++i < 513)
		swap[i] = info->valid_indexes_2[top][i];
	i = -1;
	while (stack == 2 && ++i < 513)
		info->valid_indexes_2[top][i] = info->valid_indexes_2[top + 1][i];
	i = -1;
	while (stack == 2 && ++i < 513)
		info->valid_indexes_2[top + 1][i] = swap[i];
}

void	sort_paths(t_info *info)
{
	int		i;

	i = -1;
	while (info->path_n_1 > 1 && info->valid_indexes[++i + 1][0] != EMPTY)
	{
		if (info->rooms[info->valid_indexes[i + 1][0]]->length
		< info->rooms[info->valid_indexes[i][0]]->length)
		{
			swap_paths(info, i, 1);
			i = -1;
		}
	}
	i = -1;
	while (info->path_n_2 > 1 && info->valid_indexes_2[++i + 1][0] != EMPTY)
	{
		if (info->rooms[info->valid_indexes_2[i + 1][0]]->length_2
		< info->rooms[info->valid_indexes_2[i][0]]->length_2)
		{
			swap_paths(info, i, 2);
			i = -1;
		}
	}
}
