/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:04:26 by elindber          #+#    #+#             */
/*   Updated: 2020/07/24 14:42:44 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	copy_check_rooms(t_info *info)
{
	int		i;

	i = 0;
	while (info->check_rooms[i] != EMPTY)
	{
		info->check_rooms[i] = EMPTY;
		i++;
	}
	i = 0;
	while (info->tmp_string[i] != EMPTY)
	{
		info->check_rooms[i] = info->tmp_string[i];
		i++;
	}
	i = 0;
	while (info->tmp_string[i] != EMPTY)
	{
		info->tmp_string[i] = EMPTY;
		i++;
	}
}

void	add_to_next_round(t_info *info, int s, int i)
{
	int		t;

	t = 0;
	s += 0;
	if (i == info->end_index
	|| (info->rooms[s]->flow == 1 && info->rooms[i]->flow == 1))
		return ;
	while (info->tmp_string[t] != EMPTY)
		t++;
	info->tmp_string[t] = i;
}

void	start_over_or_continue(t_info *info, int index)
{
	if (index != info->end_index && info->check_rooms[0] >= 0
	&& info->tmp_string[0] >= 0)
	{
		copy_check_rooms(info);
		info->level++;
		find_paths(info, -1, 0, 0);
	}
	else if (info->path_saved == 1)
	{
		info->path_saved = 0;
		get_links_for_start(info, 0, 0, 0);
		find_paths(info, -1, 0, 0);
	}
}

void	set_visited(t_info *info, int s, int l)
{
	info->rooms[l]->visited = info->rooms[l]->start_or_end == 2 ? 0 : 1;
	info->rooms[l]->level = info->rooms[l]->start_or_end == 2
	? INT_MAX : info->level;
	add_to_path(info, s, l, -1);
	add_to_next_round(info, s, l);
}

void	get_links(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	if (!(info->index_stack = (int**)malloc(sizeof(int*) * info->link_amnt)))
		exit_error(ERR_MALLOC, info);
	while (i < info->link_amnt)
	{
		if (!(info->index_stack[i] = (int*)malloc(sizeof(int) * 513)))
			exit_error(ERR_MALLOC, info);
		while (t < 513)
		{
			info->index_stack[i][t] = EMPTY;
			t++;
		}
		t = 0;
		i++;
	}
	get_links_for_start(info, 0, 0, 0);
	find_paths(info, -1, 0, 0);
}
