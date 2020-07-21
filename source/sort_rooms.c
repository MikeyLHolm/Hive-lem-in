/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:34:22 by elindber          #+#    #+#             */
/*   Updated: 2020/07/21 16:19:45 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		find_a_room(t_info *info, char *to_find)
{
	int		start;
	int		end;
	int		cmp;

	start = 0;
	end = info->room_amnt - 1;
	cmp = end / 2;
	while (start <= end)
	{
		if (ft_strcmp(info->rooms[cmp]->name, to_find) == 0)
			return (cmp);
		else if (ft_strcmp(info->rooms[cmp]->name, to_find) > 0)
		{
			end = cmp - 1;
			cmp /= 2;
		}
		else
		{
			start = cmp + 1;
			cmp = start + ((end - start) / 2);
		}
	}
	// maybe call exit_error here
	return (-1);
}

void	copy_room(t_room *src, t_room *dst, int mallocs)
{
	char	*tmp;

	if (mallocs == 1)
	{
		tmp = ft_strdup(src->name);
		ft_strdel(&dst->name);
		dst->name = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strdup(src->link_string);
		ft_strdel(&dst->link_string);
		dst->link_string = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		dst->name = ft_strdup(src->name);
		dst->link_string = ft_strdup(src->link_string);
	}	
	dst->start_or_end = src->start_or_end;
	dst->visited = src->visited;
	dst->path = src->path;
	dst->level = src->level;
	dst->y = src->y;
	dst->x = src->x;

}

void	swap_rooms(t_info *info, int a, int b)
{
	t_room	*swap;

	if (!(swap = (t_room*)malloc(sizeof(t_room))))
		exit_error(ERR_MALLOC, info);
	copy_room(info->rooms[a], swap, 0);
	copy_room(info->rooms[b], info->rooms[a], 1);
	copy_room(swap, info->rooms[b], 1);
	free(swap->name);
	free(swap->link_string);
	free(swap);
}

void	first_from_index(t_info *info, int i)
{
	int		first;
	int		placement;

	first = i + 1;
	placement = i;
	while (info->rooms[i] != NULL)
	{
		if (ft_strcmp(info->rooms[i]->name, info->rooms[first]->name) < 0)
			first = i;
		i++;
		if (info->rooms[i] != NULL)
		{
			if (info->rooms[placement]->x == info->rooms[i]->x
			&& info->rooms[placement]->y == info->rooms[i]->y)
				exit_error(ERR_ROOM_DUP_COORD, info);
			else if (!(ft_strcmp(info->rooms[placement]->name, info->rooms[i]->name)))
				exit_error(ERR_ROOM_DUP_NAME, info);

		}
	}
	swap_rooms(info, first, placement);
	if (info->rooms[placement + 1] != NULL)
	{
		info->rooms[placement]->links = ft_strsplit(info->rooms[placement]->link_string, ' ');
		free(info->rooms[placement]->link_string);
		if (info->rooms[placement]->start_or_end != 0)
		{
			if (info->rooms[placement]->start_or_end == 1)
				info->start_index = placement;
			else
				info->end_index = placement;
		}
	}
}

void	malloc_for_valid_indexes(t_info *info)
{
	int	i;
	int x;

	i = 0;
	x = 0;
	if (!(info->valid_indexes = (int**)malloc(sizeof(int*) * info->max_paths + 1))
	|| !(info->valid_indexes_2 = (int**)malloc(sizeof(int*) * info->max_paths + 1))
	|| !(info->valid_paths = (char**)malloc(sizeof(char*) * info->max_paths + 1))
	|| !(info->valid_paths_2 = (char**)malloc(sizeof(char*) * info->max_paths + 1)))
		exit_error(ERR_MALLOC, info);
	while (i < info->max_paths + 1)
	{
		if (!(info->valid_indexes[i] = (int*)malloc(sizeof(int) * 513))
		|| !(info->valid_indexes_2[i] = (int*)malloc(sizeof(int) * 513)))
			exit_error(ERR_MALLOC, info);
		while (x < 513)
		{
			info->valid_indexes[i][x] = EMPTY;
			info->valid_indexes_2[i][x] = EMPTY;
			x++;
		}
		x = 0;
		i++;
	}
}

void	sort_rooms(t_info *info)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (info->rooms[i + 1] != NULL)
	{
		first_from_index(info, i);
		i++;
	}
	info->rooms[i]->links = ft_strsplit(info->rooms[i]->link_string, ' ');
	if (info->rooms[i]->start_or_end != 0)
	{
		if (info->rooms[i]->start_or_end == 1)
			info->start_index = i;
		else
			info->end_index = i;
	}
	i = 0;
	while (info->rooms[info->start_index]->links[i] != NULL)
		i++;
	while (info->rooms[info->end_index]->links[x] != NULL)
		x++;
	info->max_paths = i < x ? i : x;
	malloc_for_valid_indexes(info);
}
