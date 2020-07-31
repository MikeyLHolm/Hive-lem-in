/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 14:22:54 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/31 13:59:01 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Coloring for paths in -v and -p.
*/

static void		path_color(char *room, int n)
{
	int			color;

	color = n % 10;
	if (color == 0)
		ft_printf(WHITE "%s" RESET " ", room);
	else if (color == 1)
		ft_printf(GREEN "%s" RESET " ", room);
	else if (color == 2)
		ft_printf(YELLOW "%s" RESET " ", room);
	else if (color == 3)
		ft_printf(BLUE "%s" RESET " ", room);
	else if (color == 4)
		ft_printf(MAGENTA "%s" RESET " ", room);
	else if (color == 5)
		ft_printf(CYAN "%s" RESET " ", room);
	else if (color == 6)
		ft_printf(RED "%s" RESET " ", room);
	else if (color == 7)
		ft_printf(BOLD_GREEN "%s" RESET " ", room);
	else if (color == 8)
		ft_printf(BOLD_YELLOW "%s" RESET " ", room);
	else if (color == 9)
		ft_printf(BOLD_CYAN "%s" RESET " ", room);
}

/*
**	With multiple path-sets prints the other sets.
*/

static void		print_other_paths(t_info *info, int i, int y)
{
	ft_putstr("OR\n");
	while (info->valid_indexes_2[y][0] != EMPTY)
	{
		ft_putchar('[');
		while (info->valid_indexes_2[y][i] != EMPTY)
		{
			path_color(info->rooms[info->valid_indexes_2[y][i]]->name, y);
			i++;
		}
		ft_putstr("]\n");
		i = 0;
		y++;
	}
}

/*
**	Prints different found paths.
*/

void			print_paths(t_info *info)
{
	int			y;
	int			i;

	y = 0;
	while (info->valid_indexes[y][0] != EMPTY)
	{
		i = 0;
		ft_putchar('[');
		while (info->valid_indexes[y][i] != EMPTY)
		{
			path_color(info->rooms[info->valid_indexes[y][i]]->name, y);
			i++;
		}
		ft_putstr("]\n");
		y++;
	}
	ft_putchar('\n');
	if (info->path_n_2 > 0)
		print_other_paths(info, 0, 0);
	ft_putchar('\n');
}

/*
**	Verbose mode coloring for ants.
*/

static void		ant_color(char *ant, char *room, int color)
{
	if (color == 0)
		ft_printf(WHITE "L%s-%s" RESET " ", ant, room);
	else if (color == 1)
		ft_printf(GREEN "L%s-%s" RESET " ", ant, room);
	else if (color == 2)
		ft_printf(YELLOW "L%s-%s" RESET " ", ant, room);
	else if (color == 3)
		ft_printf(BLUE "L%s-%s" RESET " ", ant, room);
	else if (color == 4)
		ft_printf(MAGENTA "L%s-%s" RESET " ", ant, room);
	else if (color == 5)
		ft_printf(CYAN "L%s-%s" RESET " ", ant, room);
	else if (color == 6)
		ft_printf(RED "L%s-%s" RESET " ", ant, room);
	else if (color == 7)
		ft_printf(BOLD_GREEN "L%s-%s" RESET " ", ant, room);
	else if (color == 8)
		ft_printf(BOLD_YELLOW "L%s-%s" RESET " ", ant, room);
	else if (color == 9)
		ft_printf(BOLD_CYAN "L%s-%s" RESET " ", ant, room);
}

/*
**	General printer for ant location output during ant flow.
*/

void			print_ant(char *ant, t_info *info, int i, char *room)
{
	int			color;

	color = i % 10;
	if (info->flag_storage & VERBOSE)
		ant_color(ant, room, color);
	else
	{
		write(1, "L", 1);
		ft_putstr(ant);
		write(1, "-", 1);
		ft_putstr(room);
		write(1, " ", 1);
	}
}
