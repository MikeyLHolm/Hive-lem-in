/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:10:11 by elindber          #+#    #+#             */
/*   Updated: 2020/07/31 14:22:20 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	add_link(t_info *info, char *line, int link)
{
	char		**link_data;

	link_data = ft_strsplit(line, '-');
	add_links_for_rooms(info, link_data[0], link_data[1]);
	if (!info->start)
		exit_error(ERR_ROOM_NO_START, info);
	if (!info->end)
		exit_error(ERR_ROOM_NO_END, info);
	if ((ft_strequ(link_data[0], info->start)
	&& ft_strequ(link_data[1], info->end))
	|| (ft_strequ(link_data[0], info->end)
	&& ft_strequ(link_data[1], info->start)))
		info->start_end_link = 1;
	free_2d_array(link_data);
	return (link);
}

static void	room_info(t_info *info, char *line, int i, int start_end)
{
	char		**room_data;

	if (line[0] == 'L')
		exit_error(ERR_ROOM_STARTS_L, info);
	room_data = ft_strsplit(line, ' ');
	room_error_check(info, room_data);
	if (!(info->rooms[i] = (t_room*)malloc(sizeof(t_room))))
		exit_error(ERR_MALLOC, info);
	info->rooms[i]->name = ft_strdup(room_data[0]);
	info->rooms[i]->x = ft_atoi(room_data[1]);
	info->rooms[i]->y = ft_atoi(room_data[2]);
	info->rooms[i]->start_or_end = start_end;
	init_room_info(info, i);
	if (!(info->rooms[i]->link_string = ft_strnew(0)))
		exit_error(ERR_MALLOC, info);
	if (start_end > 0)
		info->rooms[i]->level = start_end == 1 ? 0 : INT_MAX;
	else
		info->rooms[i]->level = -1;
	if (start_end == 1 && !info->start)
		info->start = ft_strdup(room_data[0]);
	else if (start_end == 2 && !info->end)
		info->end = ft_strdup(room_data[0]);
	free_2d_array(room_data);
}

static void	parse_rooms_and_links(t_output *op, t_info *info, int rms, int lnk)
{
	int			start_end;
	int			tmp;

	tmp = -1;
	while (op != NULL)
	{
		if (!(ft_isprint(op->line[0])))
			return ;
		if (ft_strstr(op->line, "##start") || ft_strstr(op->line, "##end"))
		{
			start_end = validate_command(info, op->line);
			tmp = 2;
		}
		tmp--;
		if (ft_strchr(op->line, ' ') && op->line[0] != '#')
		{
			if (lnk)
				exit_error(ERR_BAD_LINK, info);
			start_end = tmp == 0 ? start_end : 0;
			room_info(info, op->line, rms++, start_end);
		}
		if (ft_strchr(op->line, '-') && !(ft_strchr(op->line, ' ')))
			add_link(info, op->line, lnk++);
		op = op->next;
	}
}

static void	run_data_parsing(t_info *info, t_output *tmp2, int rooms)
{
	t_output	*tmp;

	tmp = tmp2;
	if (rooms == 0 || info->link_amnt == 0)
		rooms == 0 ? exit_error(ERR_ROOM_NO_ROOMS, info) :
		exit_error(ERR_NO_LINK, info);
	if (!(info->rooms = (t_room**)malloc(sizeof(t_room*) * rooms + 1)))
		exit_error(ERR_MALLOC, info);
	info->rooms[rooms] = NULL;
	info->room_amnt = rooms;
	parse_rooms_and_links(tmp2, info, 0, 0);
	if (!info->start || !info->end)
		!info->start ? exit_error(ERR_ROOM_NO_START, info) :
		exit_error(ERR_ROOM_NO_END, info);
	while (tmp != NULL)
	{
		ft_putendl(tmp->line);
		tmp = tmp->next;
	}
	sort_rooms(info);
}

void		parse_map(t_output *output, t_info *info)
{
	t_output	*tmp;
	t_output	*tmp2;
	char		*line;
	int			rooms;

	tmp2 = output;
	rooms = 0;
	while (get_next_line(info->fd, &line))
	{
		if (!(tmp = (t_output*)malloc(sizeof(t_output))))
			exit_error(ERR_MALLOC, info);
		if (ft_strchr(line, ' ') && line[0] != '#' && line[0] != 'L')
			rooms++;
		if (ft_strchr(line, '-') && !(ft_strchr(line, ' ')))
			info->link_amnt++;
		if (ft_strstr(line, "#Here is the number of lines required:"))
			get_required_lines(info, line);
		tmp->line = ft_strdup(line);
		output->next = tmp;
		output = output->next;
		output->next = NULL;
		free(line);
	}
	run_data_parsing(info, tmp2, rooms);
}
