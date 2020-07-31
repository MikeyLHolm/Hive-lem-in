/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_sorting_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:21:30 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 18:23:30 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			find_a_room(t_info *info, char *to_find)
{
	int		start;
	int		end;
	int		cmp;

	start = 0;
	end = info->room_amnt - 1;
	cmp = end / 2;
	if (to_find == NULL)
		return (-1);
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
	return (-1);
}

static void	copy_room(t_room *src, t_room *dst, int mallocs)
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

void		swap_rooms(t_info *info, int a, int b)
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
