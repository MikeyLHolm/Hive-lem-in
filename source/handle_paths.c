/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:45:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 17:52:16 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	create_fork(t_info *info, int room_i, int y, int t)
{
	int		s;
	int		note;
	int		fork;

	fork = 0;
	note = y;
	while (info->rooms[room_i]->links[t] != NULL && fork == 0)
	{
		s = find_a_room(info, info->rooms[room_i]->links[t]);
		if ((info->rooms[room_i]->level <= info->rooms[s]->level
		|| info->rooms[s]->level == -1) && s != info->end_index)
			fork++;
		else if (info->phase == 2 && s != info->end_index)
			fork++;
		t++;
	}
	if (fork)
	{
		t = -1;
		while (info->index_stack[y][0] != EMPTY)
			y++;
		while (info->index_stack[note][++t] != EMPTY)
			info->index_stack[y][t] = info->index_stack[note][t];
	}
}

int		last_on_path(int *path)
{
	int		i;

	i = 0;
	while (path[i + 1] != EMPTY)
		i++;
	return (path[i]);
}

void	add_to_path(t_info *info, int last, int next, int y)
{
	int		last_room;
	int		i;

	i = 0;
	if (info->rooms[last]->flow == 1 && info->rooms[next]->flow == 1)
		return ;
	while (info->index_stack[++y][0] != EMPTY)
	{
		last_room = last_on_path(info->index_stack[y]);
		if ((info->phase == 1 && info->rooms[last]->path < 0 && last_room
		== last) || (info->phase == 2 && info->rooms[last]->path_2 < 0
		&& last_room == last))
		{
			create_fork(info, last, y, 0);
			while (info->index_stack[y][i] != EMPTY)
				i++;
			info->index_stack[y][i] = next;
			if (next == info->end_index)
				save_path(info, y, 0);
			return ;
		}
	}
}
