/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_path_finding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:56:46 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 18:16:34 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	to_left(t_info *info, int i)
{
	int		t;
	int		stop;

	t = -1;
	stop = 0;
	while (i >= 0)
	{
		info->check_rooms[++t] = info->tmp_string[i];
		info->tmp_string[i] = EMPTY;
		i--;
		if (i == -1)
		{
			if (stop)
				return ;
			i = 512;
			stop++;
			while (info->tmp_string[i] == EMPTY)
				i--;
		}
	}
}

static void	from_the_middle(t_info *info, int direction)
{
	int		i;
	int		t;

	i = -1;
	t = -1;
	while (info->check_rooms[++i] != EMPTY)
	{
		info->tmp_string[i] = info->check_rooms[i];
		info->check_rooms[i] = EMPTY;
	}
	i = direction == 1 ? i / 2 : i / 2 + 1;
	while (direction == 2 && info->tmp_string[i] != EMPTY)
	{
		info->check_rooms[++t] = info->tmp_string[i];
		info->tmp_string[i] = EMPTY;
		i++;
		i = info->tmp_string[i] == EMPTY ? 0 : i;
	}
	if (direction == 1)
		to_left(info, i);
}

void		reorder_check_rooms(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	if (info->round == 2)
	{
		while (info->check_rooms[i] != EMPTY)
		{
			info->tmp_string[i] = info->check_rooms[i];
			i++;
		}
		while (--i >= 0)
			info->check_rooms[i] = info->tmp_string[t++];
	}
	else if (info->round == 3)
		from_the_middle(info, 2);
	else
		from_the_middle(info, 1);
	i = -1;
	while (++i < 513)
		info->tmp_string[i] = EMPTY;
}

void		find_paths(t_info *info, int i, int j, int s)
{
	int		l;

	while (info->check_rooms[++i] != EMPTY && info->path_saved == 0)
	{
		s = info->check_rooms[i];
		if (info->phase == 1 && info->rooms[s]->level > 1
		&& info->rooms[s]->path < 0)
			delete_dead_end(info, s);
		while (info->rooms[s]->links[j] != NULL
		&& info->path_saved == 0)
		{
			l = find_a_room(info,
			info->rooms[s]->links[j++]);
			if (info->rooms[l]->visited == 0)
				set_visited(info, s, l);
			if (l == info->end_index)
				break ;
		}
		info->rooms[s]->visited++;
		j = 0;
	}
	start_over_or_continue(info, l);
}

void		get_links_for_start(t_info *info, int i, int s, int t)
{
	while (s < 513)
	{
		info->check_rooms[s] = EMPTY;
		s++;
	}
	while (info->rooms[info->start_index]->links[i] != NULL)
	{
		s = find_a_room(info, info->rooms[info->start_index]->links[i]);
		if (info->rooms[s]->visited == 0)
		{
			info->rooms[s]->visited = 1;
			info->rooms[s]->level = info->level;
			info->index_stack[t][0] = s;
			info->check_rooms[t] = s;
			t++;
		}
		i++;
	}
	if (info->round > 1)
		reorder_check_rooms(info);
	info->rooms[info->start_index]->visited = 2;
	info->level++;
}
