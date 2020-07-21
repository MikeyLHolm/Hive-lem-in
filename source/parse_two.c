/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:10:11 by elindber          #+#    #+#             */
/*   Updated: 2020/07/21 09:59:29 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_links_for_rooms(t_info *info, char *room1, char *room2)
{
	char	*tmp;
	char	*add;
	int		i;
	int		added;

	i = 0;
	added = 0;
	while (info->rooms[i] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, room1))
		{
			add = ft_strjoin(room2, " ");
			if (ft_strstr(info->rooms[i]->link_string, add))
				exit_error(ERR_DUP_LINK, info);
			tmp = ft_strjoin(info->rooms[i]->link_string, add);
			free(info->rooms[i]->link_string);
			info->rooms[i]->link_string = ft_strdup(tmp);
			free(tmp);
			free(add);
			added++;
		}
		else if (ft_strequ(info->rooms[i]->name, room2))
		{
			add = ft_strjoin(room1, " ");
			if (ft_strstr(info->rooms[i]->link_string, add))
				exit_error(ERR_DUP_LINK, info);
			tmp = ft_strjoin(info->rooms[i]->link_string, add);
			free(info->rooms[i]->link_string);
			info->rooms[i]->link_string = ft_strdup(tmp);
			free(tmp);
			free(add);
			added++;
		}
		if (added == 2)
			return ;
		i++;
	}
	exit_error(ERR_BAD_LINK, info);
}

int		add_link(t_info *info, char *line, int i)
{
	char	**link_data;

	link_data = ft_strsplit(line, '-');
	i += 0;
	add_links_for_rooms(info, link_data[0], link_data[1]);
	free_2d_array(link_data);
	return (1);
}

int		room_info(t_info *info, char *line, int i, int start_end)
{
	char	**room_data;

	if (line[0] == 'L')
		exit_error(ERR_ROOM_STARTS_L, info);
	room_data = ft_strsplit(line, ' ');
	if (!(info->rooms[i] = (t_room*)malloc(sizeof(t_room))))
		return (0);
	info->rooms[i]->name = ft_strdup(room_data[0]);
	info->rooms[i]->x = ft_atoi(room_data[1]);
	info->rooms[i]->y = ft_atoi(room_data[2]);
	info->rooms[i]->start_or_end = start_end;
	info->rooms[i]->visited = 0;
	info->rooms[i]->ants = 0;
	info->rooms[i]->ants_2 = 0;
	if (!(info->rooms[i]->link_string = ft_strnew(0)))
		exit_error(ERR_MALLOC, info);
	if (start_end > 0)
		info->rooms[i]->level = start_end == 1 ? 0 : INT_MAX;
	else
		info->rooms[i]->level = -1;
	info->rooms[i]->path = -1;
	info->rooms[i]->path_2 = -1;
	info->rooms[i]->flow = 0;
	if (start_end == 1 && !info->start)
		info->start = ft_strdup(room_data[0]);
	else if (start_end == 1)
		exit_error(ERR_ROOM_M_START, info);
	if (start_end == 2 && !info->end)
		info->end = ft_strdup(room_data[0]);
	else if (start_end == 2)
		exit_error(ERR_ROOM_M_END, info);
	free_2d_array(room_data);
	return (1);
}

void	parse_rooms_and_links(t_output *op, t_info *info)
{
	int		i;
	int		start_end;
	int		tmp;
	int		rooms;
	int		links;

	i = 0;
	tmp = -1;
	rooms = 0;
	links = 0;
	start_end = 0;
	while (op != NULL)
	{
		if (ft_strstr(op->line, "##start") || ft_strstr(op->line, "##end"))
		{
			start_end = ft_strstr(op->line, "##start") ? 1 : 2;
			tmp = 1;
		}
		else
			tmp--;
		if (ft_strchr(op->line, ' ') && op->line[0] != '#')
		{
			start_end = tmp == 0 ? start_end : 0;
			room_info(info, op->line, rooms, start_end);
			rooms++;
		}
		if (ft_strchr(op->line, '-') && !(ft_strchr(op->line, ' ')))
		{
			add_link(info, op->line, links);
			links++;
		}
		ft_printf("%s\n", op->line);
		op = op->next;
		i++;
	}
}

int		parse_v2(t_output *output, t_info *info)
{
	t_output	*tmp;
	t_output	*tmp2;
	char		*line;
	int			rooms;
	int			links;

	tmp2 = output;
	rooms = 0;
	links = 0;
	// add protection vs map containing only nbr of ants. atm segfaults here since there is no more lines
	while (get_next_line(info->tmpfd, &line))
	{
		if (!(tmp = (t_output*)malloc(sizeof(t_output))))
			return (0);
		if (ft_strchr(line, ' ') && line[0] != '#' && line[0] != 'L') // change conditon so that the hashtag OR L can not be in the 0 index of line
			rooms++;
		if (ft_strchr(line, '-') && !(ft_strchr(line, ' ')))
			info->link_amnt++;
		tmp->line = ft_strdup(line);
		output->next = tmp;
		output = output->next;
		output->next = NULL;
		free(line);
	}
	if (!(info->rooms = (t_room**)malloc(sizeof(t_room*) * rooms + 1)))
		exit_error(ERR_MALLOC, info);
	info->rooms[rooms] = NULL;
	info->room_amnt = rooms;
	parse_rooms_and_links(tmp2, info);
	if (!info->start || !info->end)
		!info->start ? exit_error(ERR_ROOM_NO_START, info) : exit_error(ERR_ROOM_NO_END, info);
	sort_rooms(info);
	return (1);
}
