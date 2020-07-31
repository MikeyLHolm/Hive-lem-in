/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:30:44 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 18:17:30 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Moves ant from the start to the queue.
*/

static void		ant_to_first_room(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = 0;
	while (info->rooms[info->valid_indexes[i][0]]->ant_queue[t] == -1)
		t++;
	if (info->rooms[info->valid_indexes[i][0]]->ant_queue[t] <= 0)
		return ;
	ant = ft_itoa(info->rooms[info->valid_indexes[i][0]]->ant_queue[t]);
	print_ant(ant, info, i, info->rooms[info->valid_indexes[i][0]]->name);
	free(ant);
	info->rooms[info->valid_indexes[i][0]]->visited = 1;
	info->rooms[info->valid_indexes[i][0]]->ant_id =
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t];
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t] = -1;
	info->ants_at_start--;
}

/*
**	Moves ants on path and prints the L1-2.
*/

static void		move_path(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = info->rooms[info->valid_indexes[i][0]]->length;
	while (--t >= 0)
	{
		if (info->rooms[info->valid_indexes[i][t]]->visited == 1
		&& info->rooms[info->valid_indexes[i][t + 1]]->visited == 0)
		{
			ant = ft_itoa(info->rooms[info->valid_indexes[i][t]]->ant_id);
			print_ant(ant, info, i,
			info->rooms[info->valid_indexes[i][t + 1]]->name);
			free(ant);
			info->rooms[info->valid_indexes[i][t + 1]]->ant_id =
			info->rooms[info->valid_indexes[i][t]]->ant_id;
			info->rooms[info->valid_indexes[i][t + 1]]->visited =
			info->valid_indexes[i][t + 1] == info->end_index ? 0 : 1;
			if (info->valid_indexes[i][t + 1] == info->end_index)
				info->ants_at_end++;
			info->rooms[info->valid_indexes[i][t]]->visited = 0;
			info->rooms[info->valid_indexes[i][t]]->ant_id = 0;
		}
	}
	if (info->ants_at_start > 0)
		ant_to_first_room(info, i);
}

/*
**	Runs turns of ant flow.
*/

static void		print_turns(t_info *info)
{
	int		i;

	i = 0;
	while (info->ants_at_end < info->ants)
	{
		move_path(info, i);
		i++;
		if (info->ants_at_end == info->ants)
		{
			if (i != 0)
				ft_putchar('\n');
			return ;
		}
		if (i == info->path_n_1)
		{
			i = 0;
			info->lines++;
			ft_putchar('\n');
		}
	}
}

/*
**	Main ant_flow dispatcher.
*/

void			ant_flow(t_info *info)
{
	int		i;
	int		y;

	i = -1;
	y = -1;
	while (info->valid_indexes[++y][0] != EMPTY)
	{
		while (info->valid_indexes[y][++i] != EMPTY)
			info->rooms[info->valid_indexes[y][i]]->visited = 0;
		i = -1;
	}
	info->ants_at_start = info->ants;
	divide_to_paths(info, 0, 0, 0);
	info->ants_at_start = info->ants;
	print_turns(info);
}
