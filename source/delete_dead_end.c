/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_dead_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 13:29:49 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 15:35:49 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	delete_branch(t_info *info, int index)
{
	int		i;
	int		prev;

	i = 0;
	while (info->rooms[index]->links[i] != NULL)
	{
		i++;
		if (i > 2)
			return ;
	}
	prev = find_a_room(info, info->rooms[index]->links[0]);
	if (info->rooms[prev]->level > info->rooms[index]->level)
		prev = find_a_room(info, info->rooms[index]->links[1]);
	free_2d_array(info->rooms[index]->links);
	if (!(info->rooms[index]->links = (char**)malloc(sizeof(char*) * 1)))
		exit_error(ERR_MALLOC, info);
	info->rooms[index]->links[0] = NULL;
	info->ants_at_start += 1;
	if (info->flag_storage & VERBOSE)
		ft_printf(BOLD_GREEN "ROOMS DELETED: %d\n" RESET,
		info->ants_at_start - info->ants);
	delete_branch(info, prev);
}

void	delete_dead_end(t_info *info, int dead_end)
{
	int		i;
	int		prev;

	i = 0;
	while (info->rooms[dead_end]->links[i] != NULL)
	{
		i++;
		if (i > 1)
			return ;
	}
	prev = find_a_room(info, info->rooms[dead_end]->links[0]);
	if (prev < 0 || prev == info->end_index || info->rooms[prev]->path > -1)
		return ;
	delete_branch(info, prev);
}
