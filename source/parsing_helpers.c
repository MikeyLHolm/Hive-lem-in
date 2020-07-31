/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:14:29 by elindber          #+#    #+#             */
/*   Updated: 2020/07/30 17:17:18 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_new_link(t_info *info, int i, char *room)
{
	char	*add;
	char	*add2;
	char	*tmp;

	add2 = ft_strjoin(" ", room);
	add = ft_strjoin(add2, " ");
	if (ft_strstr(info->rooms[i]->link_string, add))
		exit_error(ERR_DUP_LINK, info);
	tmp = ft_strjoin(info->rooms[i]->link_string, add);
	free(info->rooms[i]->link_string);
	info->rooms[i]->link_string = ft_strdup(tmp);
	free(tmp);
	free(add);
	free(add2);
}

void	add_links_for_rooms(t_info *info, char *room1, char *room2)
{
	int			i;
	int			added;

	i = 0;
	added = 0;
	while (info->rooms[i] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, room1))
		{
			add_new_link(info, i, room2);
			added++;
		}
		else if (ft_strequ(info->rooms[i]->name, room2))
		{
			add_new_link(info, i, room1);
			added++;
		}
		if (added == 2)
			return ;
		i++;
	}
	exit_error(ERR_BAD_LINK, info);
}

void	room_error_check(t_info *info, char **room_data)
{
	if (ft_strchr(room_data[0], '-'))
		exit_error(ERR_ROOM_NAME_DASH, info);
	if (room_data[3] != NULL)
		exit_error(ERR_ROOM_ARGS_MANY, info);
	if (room_data[1] == NULL || room_data[2] == NULL)
		exit_error(ERR_ROOM_ARGS_FEW, info);
}

void	init_room_info(t_info *info, int i)
{
	info->rooms[i]->visited = 0;
	info->rooms[i]->ants = 0;
	info->rooms[i]->ants_2 = 0;
	info->rooms[i]->path = -1;
	info->rooms[i]->path_2 = -1;
	info->rooms[i]->flow = 0;
}

int		validate_command(t_info *info, char *line)
{
	int		start_end;

	if (info->start && ft_strstr(line, "##start"))
		exit_error(ERR_ROOM_M_START, info);
	else if (info->end && ft_strstr(line, "##end"))
		exit_error(ERR_ROOM_M_END, info);
	start_end = ft_strstr(line, "##start") ? 1 : 2;
	return (start_end);
}
