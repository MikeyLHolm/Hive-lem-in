/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_ants_to_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:17:12 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 18:17:57 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	divide_paths_data(t_info *info, int antnb, int i, int tab)
{
	tab = info->rooms[info->valid_indexes[i][0]]->ants;
	info->rooms[info->valid_indexes[i][0]]->ant_queue[tab] = antnb;
	info->rooms[info->valid_indexes[i][0]]->ants++;
	info->rooms[info->valid_indexes[i][0]]->cost++;
	info->ants_at_start--;
	return (tab);
}

/*
**	Helper for D_T_P.
*/

static int	cmp_loop(t_info *info, int cmp, int i)
{
	cmp = info->rooms[info->valid_indexes[i][0]]->cost;
	i = 0;
	while (info->rooms[info->valid_indexes[i][0]]->cost > cmp)
		i++;
	return (i);
}

/*
**	Divides ants to paths during first ant flow.
*/

void		divide_to_paths(t_info *info, int i, int tab, int cmp)
{
	int		antnb;

	antnb = 1;
	while (info->ants_at_start > 0)
	{
		if (info->path_n_1 == 1)
			tab = divide_paths_data(info, antnb++, i, tab);
		else if (info->rooms[info->valid_indexes[i][0]]->cost
		<= info->rooms[info->valid_indexes[i + 1][0]]->cost)
		{
			if (info->rooms[info->valid_indexes[i][0]]->cost
			== info->rooms[info->valid_indexes[i + 1][0]]->cost)
				i = cmp_loop(info, cmp, i);
			tab = divide_paths_data(info, antnb++, i, tab);
		}
		else if (info->rooms[info->valid_indexes[i][0]]->cost
		> info->rooms[info->valid_indexes[i + 1][0]]->cost)
			tab = divide_paths_data(info, antnb++, ++i, tab);
		if (i == info->path_n_1 - 1
		|| info->rooms[info->valid_indexes[i][0]]->cost
		< info->rooms[info->valid_indexes[i + 1][0]]->cost)
			i = 0;
	}
}
