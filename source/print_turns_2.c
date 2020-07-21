/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_turns_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:57:59 by elindber          #+#    #+#             */
/*   Updated: 2020/07/16 15:12:56 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	ant_to_first_room(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = 0;
	while (info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[t] == -1)
		t++;
	if (info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[t] <= 0)
		return ;
	ant = ft_itoa(info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[t]);
	ft_printf("L%s-%s ", ant, info->rooms[info->valid_indexes_2[i][0]]->name);
	free(ant);
	info->rooms[info->valid_indexes_2[i][0]]->visited = 1;
	info->rooms[info->valid_indexes_2[i][0]]->ant_id =
	info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[t];
	info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[t] = -1;
	info->ants_at_start--;
}

static void	move_path(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = info->rooms[info->valid_indexes_2[i][0]]->length_2 - 1;
	while (t >= 0)
	{
		if (info->rooms[info->valid_indexes_2[i][t]]->ant_id > 0 // probably this first condition can be removed
		&& info->rooms[info->valid_indexes_2[i][t]]->visited == 1
		&& info->rooms[info->valid_indexes_2[i][t + 1]]->visited == 0)
		{
			ant = ft_itoa(info->rooms[info->valid_indexes_2[i][t]]->ant_id);
			ft_printf("L%s-%s ", ant,
			info->rooms[info->valid_indexes_2[i][t + 1]]->name);
			free(ant);
			info->rooms[info->valid_indexes_2[i][t + 1]]->ant_id =
			info->rooms[info->valid_indexes_2[i][t]]->ant_id;
			info->rooms[info->valid_indexes_2[i][t + 1]]->visited =
			info->valid_indexes_2[i][t + 1] == info->end_index ? 0 : 1;
			if (info->valid_indexes_2[i][t + 1] == info->end_index)
				info->ants_at_end++;
			info->rooms[info->valid_indexes_2[i][t]]->visited = 0;
			info->rooms[info->valid_indexes_2[i][t]]->ant_id = 0;
		}
		t--;
	}
	if (info->ants_at_start > 0)
		ant_to_first_room(info, i);
}

void		print_turns_2(t_info *info)
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
		if (i == info->path_amount_2)
		{
			i = 0;
			info->lines++;
			ft_putchar('\n');
		}
	}
}
