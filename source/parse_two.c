/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:10:11 by elindber          #+#    #+#             */
/*   Updated: 2020/07/15 15:33:16 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


int		count_size(char **links) // maybe not needed anymore?
{
	int		i;

	i = 0;
	while (links[i] != NULL)
		i++;
	return (i);
}

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
		//	free_2d_array(info->rooms[i]->links);
			add = ft_strjoin(room2, " ");
			tmp = ft_strjoin(info->rooms[i]->link_string, add);
			free(info->rooms[i]->link_string);
			info->rooms[i]->link_string = ft_strdup(tmp);
			free(tmp);
			free(add);
		//	info->rooms[i]->links = ft_strsplit(info->rooms[i]->link_string, ' ');
			added++;
		}
		else if (ft_strequ(info->rooms[i]->name, room2))
		{
		//	free_2d_array(info->rooms[i]->links);
			add = ft_strjoin(room1, " ");
			tmp = ft_strjoin(info->rooms[i]->link_string, add);
			free(info->rooms[i]->link_string);
			info->rooms[i]->link_string = ft_strdup(tmp);
			free(tmp);
			free(add);
		//	info->rooms[i]->links = ft_strsplit(info->rooms[i]->link_string, ' ');
			added++;
		}
		if (added == 2)
			return ;
		i++;
	}
}

int		add_link(t_info *info, char *line, int i)
{
	char	**link_data;

	link_data = ft_strsplit(line, '-');
//	link_data[2] = NULL;
	i += 0;
//	if (!(info->links[i] = (char**)malloc(sizeof(char*) * 3)))
//		return (0);
//	info->links[i][0] = ft_strdup(link_data[0]);
//	info->links[i][1] = ft_strdup(link_data[1]);
//	info->links[i][2] = NULL;
	add_links_for_rooms(info, link_data[0], link_data[1]);
	free_2d_array(link_data);
	return (1);
}

int		room_info(t_info *info, char *line, int i, int start_end)
{
	char	**room_data;

	room_data = ft_strsplit(line, ' ');
//	room_data[3] = NULL;
	if (!(info->rooms[i] = (t_room*)malloc(sizeof(t_room))))
		return (0);
	info->rooms[i]->name = ft_strdup(room_data[0]);
	info->rooms[i]->x = ft_atoi(room_data[1]);
	info->rooms[i]->y = ft_atoi(room_data[2]);
	info->rooms[i]->start_or_end = start_end;
	info->rooms[i]->visited = 0;
	info->rooms[i]->ants = 0;
	if (!(info->rooms[i]->link_string = ft_strnew(0)))
		exit_error(ERR_MALLOC);
	if (start_end > 0)
		info->rooms[i]->level = start_end == 1 ? 0 : INT_MAX;
	else
		info->rooms[i]->level = -1;
	info->rooms[i]->path = -1;
	info->rooms[i]->path_2 = -1;
	info->rooms[i]->flow = 0;
	if (start_end == 1)
		info->start = ft_strdup(room_data[0]);
	else if (start_end == 2)
		info->end = ft_strdup(room_data[0]);
	free_2d_array(room_data);
	return (1);
}

void	print_lines(t_output *op, t_info *info)
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
		info->map[i] = ft_strdup(op->line); // maybe this can be removed
		if (ft_strstr(op->line, "##start") || ft_strstr(op->line, "##end"))
		{
			start_end = ft_strstr(op->line, "##start") ? 1 : 2;
			tmp = 1;
		}
		else
			tmp--;
		if (ft_strchr(op->line, ' ') && !(ft_strchr(op->line, '#')))
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

int		parse_v2(t_output *output, t_info *info, int count)
{
	t_output	*tmp;
	t_output	*tmp2;
	char		*line;
	int			rooms;
	int			links;

	tmp2 = output;
	rooms = 0;
	links = 0;
	while (get_next_line(info->tmpfd, &line))
	{
		if (!(tmp = (t_output*)malloc(sizeof(t_output))))
			return (0);
		if (ft_strchr(line, ' ') && !(ft_strchr(line, '#'))) // change conditon so that the hashtag OR L can not be in the 0 index of line
			rooms++;
		if (ft_strchr(line, '-') && !(ft_strchr(line, ' ')))
			info->link_amnt++;
		tmp->line = ft_strdup(line);
		output->next = tmp;
		output = output->next;
		output->next = NULL;
		free(line);
		count++;
	}
	if (!(info->map = (char**)malloc(sizeof(char*) * (count + 1))) ||
	!(info->rooms = (t_room**)malloc(sizeof(t_room*) * rooms + 1)))
//	!(info->links = (char***)malloc(sizeof(char**) * (info->link_amnt + 1))))
		exit_error(ERR_MALLOC);
	info->rooms[rooms] = NULL;
	info->room_amnt = rooms;
//	info->links[links] = NULL;
	print_lines(tmp2, info);
	sort_rooms(info);
	return (1);
}

/*
	int i = 0;
	while (info->rooms[i] != NULL)
	{
		ft_printf("room [%s]\n", info->rooms[i]->name);
		i++;
	}
	
	int i = 0;
	while (info->links[i] != NULL)
	{
		ft_printf("[%s] <-> [%s]\n", info->links[i][0], info->links[i][1]);
		i++;
	}
	*/
