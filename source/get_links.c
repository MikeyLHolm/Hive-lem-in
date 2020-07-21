/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:04:26 by elindber          #+#    #+#             */
/*   Updated: 2020/07/21 09:54:07 by mlindhol         ###   ########.fr       */
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
	if (i == info->end_index || (info->rooms[s]->flow == 1 && info->rooms[i]->flow == 1))
		return ;
	while (info->tmp_string[t] != EMPTY)
		t++;
	info->tmp_string[t] = i;
}

void	find_paths(t_info *info)
{
	int		i;
	int		j;
	int		l;
	int		s;

	i = 0;
	j = 0;
	if (info->path_saved > 0) // ultimate ending condition
		return ;
	while (info->check_rooms[i] != EMPTY && info->path_saved == 0)
	{
		s = info->check_rooms[i];
		while (info->rooms[info->check_rooms[i]]->links[j] != NULL && info->path_saved == 0)
		{
			l = find_a_room(info, info->rooms[info->check_rooms[i]]->links[j]);
			if (info->rooms[l]->visited == 0)
			{
				info->rooms[l]->visited = info->rooms[l]->start_or_end == 2 ? 0 : 1;
				if (info->rooms[l]->level < 0)
					info->rooms[l]->level = info->rooms[l]->start_or_end == 2 ? INT_MAX : info->level;
				add_to_path(info, s, l, 0);
				add_to_next_round(info, s, l);
			}
			j++;
			if (l == info->end_index)
				break ;
		}
		info->rooms[s]->visited++;
		j = 0;
		i++;
	}
	if (l != info->end_index && info->check_rooms[0] >= 0 && info->tmp_string[0] >= 0)
	{
	    copy_check_rooms(info);
		info->level++;
		find_paths(info);
	}
	else if (info->path_saved == 1)
	{
		info->path_saved = 0;
		get_links_for_start(info);
		find_paths(info);
	}
}

int		get_links_for_start(t_info *info) // change to void
{
	int		room_list[513];
	int		i;
	int		s;
	int		t;

	i = 0;
	t = 0;
	while (i < 513)
	{
		room_list[i] = EMPTY;
		info->check_rooms[i] = EMPTY;
		i++;
	}
	i = 0;
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
	t = 0;
	info->rooms[info->start_index]->visited = 2;
	info->level++;
	return (1);
}

void	get_links(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	if (!(info->paths = (char**)malloc(sizeof(char*) * info->link_amnt + 1))
	|| !(info->index_stack = (int**)malloc(sizeof(int*) * info->link_amnt)))
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
//	i = 0;
//	while (i < 513)
//	{
//		ft_printf("[%d]", info->index_stack[0][i]);
//		i++;
//	}
	get_links_for_start(info);
	find_paths(info);
//	while (info->end_reached == 0)
}
