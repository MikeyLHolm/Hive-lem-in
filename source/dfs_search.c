/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:46:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 15:30:05 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	dfs_start_over_or_continue(t_info *info, int index)
{
	if (index != info->end_index
	&& info->tmp_string[0] >= 0)
	{
		copy_check_rooms(info);
		info->level++;
		search_from_room(info);
	}
}

void	search_from_room(t_info *info)
{
	int		c;
	int		s;
	int		l;
	int		j;

	c = -1;
	j = -1;
	while (info->check_rooms[++c] != EMPTY && info->path_saved == 0)
	{
		s = info->check_rooms[c];
		while (info->rooms[s]->links[++j] != NULL && info->path_saved == 0)
		{
			l = find_a_room(info, info->rooms[s]->links[j]);
			if (info->rooms[l]->visited == 0)
				set_visited(info, s, l);
			if (l == info->end_index)
				break ;
		}
		info->rooms[s]->visited++;
		j = -1;
	}
	dfs_start_over_or_continue(info, l);
}

void	get_lvl_2_rooms(t_info *info, int i)
{
	int		j;
	int		s;
	int		t;

	j = 0;
	t = 0;
	while (info->rooms[info->lvl_1_rooms[i]]->links[j] != NULL)
	{
		s = find_a_room(info, info->rooms[info->lvl_1_rooms[i]]->links[j]);
		if (info->rooms[info->lvl_1_rooms[i]]->path_2 < 0
		&& info->rooms[s]->visited == 0)
		{
			info->rooms[s]->visited = 1;
			info->rooms[s]->level = info->level;
			info->index_stack[t][0] = info->lvl_1_rooms[i];
			info->index_stack[t][1] = s;
			info->check_rooms[t] = s;
			t++;
		}
		j++;
	}
	info->rooms[info->lvl_1_rooms[i]]->visited = 2;
	info->level++;
}

void	dfs_search(t_info *info, int i)
{
	while (info->lvl_1_rooms[++i] != EMPTY)
	{
		info->level = 2;
		get_lvl_2_rooms(info, i);
		search_from_room(info);
		reset_tmp_stacks(info);
		if (info->last_found_used_2 == 0)
			return ;
		info->path_saved = 0;
	}
}
