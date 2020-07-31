/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_second_and_third_round.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:43:12 by elindber          #+#    #+#             */
/*   Updated: 2020/07/31 14:22:36 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	save_first_level_rooms(t_info *info)
{
	int		i;

	i = -1;
	while (++i < 513)
	{
		info->lvl_1_rooms[i] = info->check_rooms[i];
		info->check_rooms[i] = EMPTY;
	}
}

static int	reset_values(t_info *info)
{
	info->phase = 2;
	info->level = 1;
	info->path_n_2 = 0;
	info->path_saved = 0;
	info->last_found_used_2 = 1;
	return (-1);
}

void		get_required_lines(t_info *info, char *line)
{
	int		i;

	i = 0;
	while (!(ft_isdigit(line[i])))
		i++;
	info->required = ft_atoi(&(line[i]));
}

void		third_round(t_info *info)
{
	int		i;

	info->round = 1;
	while (!info->accurate && info->round < 5)
	{
		i = reset_values(info);
		reset_tmp_stacks(info);
		while (info->rooms[++i] != NULL)
		{
			if (info->round > 1)
				info->rooms[i]->visited = info->rooms[i]->path_2 < 0 ? 0 : 1;
			else
				info->rooms[i]->visited = 0;
			info->rooms[i]->flow = 0;
			info->rooms[i]->path_2 = -1;
		}
		get_links_for_start(info, 0, 0, 0);
		save_first_level_rooms(info);
		dfs_search(info, -1);
		if (info->flag_storage & VERBOSE)
			print_paths(info);
		calculate_moves(info);
		info->round++;
	}
}

void		second_round(t_info *info)
{
	int		i;

	i = 0;
	info->phase = 2;
	info->level = 1;
	info->path_n_2 = 0;
	if (info->path_n_1 < 1)
		exit_error(ERR_NO_PATH, info);
	reset_tmp_stacks(info);
	while (info->rooms[i] != NULL)
	{
		info->rooms[i]->visited = 0;
		i++;
	}
	get_links_for_start(info, 0, 0, 0);
	find_paths(info, -1, 0, 0);
	if (info->valid_indexes_2[0][0] != EMPTY && (info->flag_storage & VERBOSE))
		print_paths(info);
	calculate_moves(info);
}
