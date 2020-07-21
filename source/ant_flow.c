/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:30:44 by elindber          #+#    #+#             */
/*   Updated: 2020/07/20 12:04:59 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	ft_printf("L%s-%s ", ant, info->rooms[info->valid_indexes[i][0]]->name);
	free(ant);
	info->rooms[info->valid_indexes[i][0]]->visited = 1;
	info->rooms[info->valid_indexes[i][0]]->ant_id =
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t];
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t] = -1;
	info->ants_at_start--;
}

static void		move_path(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = info->rooms[info->valid_indexes[i][0]]->length - 1;
	while (t >= 0)
	{
		if (info->rooms[info->valid_indexes[i][t]]->ant_id > 0 //maybe this first is not needed
		&& info->rooms[info->valid_indexes[i][t]]->visited == 1
		&& info->rooms[info->valid_indexes[i][t + 1]]->visited == 0)
		{
			ant = ft_itoa(info->rooms[info->valid_indexes[i][t]]->ant_id);
			ft_printf("L%s-%s ", ant,
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
		t--;
	}
	if (info->ants_at_start > 0)
		ant_to_first_room(info, i);
}

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
		if (i == info->path_amount_1)
		{
			i = 0;
			info->lines++;
			ft_putchar('\n');
		}
	}
}

static int		divide_paths_1_data(t_info *info, int antnb, int i, int tab)
{
	tab = info->rooms[info->valid_indexes[i][0]]->ants;
	info->rooms[info->valid_indexes[i][0]]->ant_queue[tab] = antnb;
	info->rooms[info->valid_indexes[i][0]]->ants++;
	info->rooms[info->valid_indexes[i][0]]->cost++;
	info->ants_at_start--;
	return (tab);
}

static void		divide_paths_2_data(t_info *info, int antnb, int i, int tab)
{
	info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[tab] = antnb;
	info->rooms[info->valid_indexes_2[i][0]]->ants_2++;
	info->rooms[info->valid_indexes_2[i][0]]->cost_2++;
	info->ants_at_start--;
}

static void		divide_to_paths_1(t_info *info)
{
	int		i;
	int		antnb;
	int		tab;
	int		cmp;

	i = 0;
	cmp = 0;
	antnb = 1;
	tab = 0;
	while (info->ants_at_start > 0)
	{
		if (info->path_amount_1 == 1)
			tab = divide_paths_1_data(info, antnb++, i, tab);
		else if (info->rooms[info->valid_indexes[i][0]]->cost
		<= info->rooms[info->valid_indexes[i + 1][0]]->cost)
		{
			if (info->rooms[info->valid_indexes[i][0]]->cost
			== info->rooms[info->valid_indexes[i + 1][0]]->cost)
			{
				cmp = info->rooms[info->valid_indexes[i][0]]->cost;
				i = 0;
				while (info->rooms[info->valid_indexes[i][0]]->cost > cmp)
					i++;
			}
			tab = divide_paths_1_data(info, antnb++, i, tab);
		}
		else if (info->rooms[info->valid_indexes[i][0]]->cost
		> info->rooms[info->valid_indexes[i + 1][0]]->cost)
			tab = divide_paths_1_data(info, antnb++, ++i, tab);
		if (i == info->path_amount_1 - 1
		|| info->rooms[info->valid_indexes[i][0]]->cost
		< info->rooms[info->valid_indexes[i + 1][0]]->cost)
			i = 0;
	}
	info->ants_at_start = info->ants;
}

static void		divide_to_paths_2(t_info *info)
{
	int		i;
	int		antnb;
	int		tab;
	int		cmp;

	i = 0;
	cmp = 0;
	antnb = 1;
	while (info->ants_at_start > 0)
	{
		if (info->path_amount_2 == 1)
		{
			tab = info->rooms[info->valid_indexes_2[i][0]]->ants_2;
			divide_paths_2_data(info, antnb, i, tab);
			// info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[tab] = antnb;
			// info->rooms[info->valid_indexes_2[i][0]]->ants_2++;
			// info->rooms[info->valid_indexes_2[i][0]]->cost_2++;
			// info->ants_at_start--;
			antnb++;
		}
		else if (info->rooms[info->valid_indexes_2[i][0]]->cost_2
		<= info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
		{
			if (info->rooms[info->valid_indexes_2[i][0]]->cost_2
			== info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
			{
				cmp = info->rooms[info->valid_indexes_2[i][0]]->cost_2;
				i = 0;
				while (info->rooms[info->valid_indexes_2[i][0]]->cost_2 > cmp)
					i++;
			}
			tab = info->rooms[info->valid_indexes_2[i][0]]->ants_2;
			divide_paths_2_data(info, antnb, i, tab);
			// info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[tab] = antnb;
			// info->rooms[info->valid_indexes_2[i][0]]->ants_2++;
			// info->rooms[info->valid_indexes_2[i][0]]->cost_2++;
			// info->ants_at_start--;
			antnb++;
		}
		else if (info->rooms[info->valid_indexes_2[i][0]]->cost_2
		> info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
		{
			i++;
			tab = info->rooms[info->valid_indexes_2[i][0]]->ants_2;
			divide_paths_2_data(info, antnb, i, tab);
			// info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[tab] = antnb;
			// info->rooms[info->valid_indexes_2[i][0]]->ants_2++;
			// info->rooms[info->valid_indexes_2[i][0]]->cost_2++;
			// info->ants_at_start--;
			antnb++;
		}
		if (i == info->path_amount_2 - 1
		|| info->rooms[info->valid_indexes_2[i][0]]->cost_2
		< info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
			i = 0;
	}
	info->ants_at_start = info->ants;
}

static void		reset_room_statuses(t_info *info, int y, int i)
{
	while (info->valid_indexes[y][0] != EMPTY)
	{
		while (info->valid_indexes[y][i] != EMPTY)
		{
			info->rooms[info->valid_indexes[y][i]]->visited = 0;
			i++;
		}
		i = 0;
		y++;
	}
	y = 0;
	while (info->valid_indexes_2[y][0] != EMPTY)
	{
		while (info->valid_indexes_2[y][i] != EMPTY)
		{
			info->rooms[info->valid_indexes_2[y][i]]->visited = 0;
			i++;
		}
		i = 0;
		y++;
	}
}

void			ant_flow(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	reset_room_statuses(info, 0, 0);
	info->ants_at_start = info->ants;
	divide_to_paths_1(info);
	if (info->valid_indexes_2[0][0] != EMPTY)
		divide_to_paths_2(info);
	if (info->path_amount_2 > 0 && info->rooms[info->valid_indexes[0][0]]->cost
	> info->rooms[info->valid_indexes_2[0][0]]->cost_2)
		print_turns_2(info);
	else
		print_turns(info);
}
