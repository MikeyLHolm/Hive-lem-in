/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:26:57 by elindber          #+#    #+#             */
/*   Updated: 2020/07/31 15:25:55 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	When direct start-end link is found. Move all ants straight to end.
*/

static void		all_ants_to_end_at_once(t_info *info)
{
	int			i;

	i = 1;
	write(1, "\n", 1);
	while (i <= info->ants)
	{
		write(1, "L", 1);
		ft_putnbr(i);
		write(1, "-", 1);
		ft_putstr(info->end);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	info->ants_at_end = info->ants_at_start;
	info->ants_at_start = 0;
}

/*
**	Initialize info struct.
*/

static void		init_info(t_info *info)
{
	int			i;

	i = 0;
	while (i < 513)
		info->tmp_string[i++] = EMPTY;
	if (!(info->flag_storage & ANTS))
		info->ants = -1;
	info->ants_at_start = 0;
	info->ants_at_end = 0;
	info->last_found_used = 1;
	info->last_found_used_2 = 1;
	info->path_n_1 = 0;
	info->path_n_2 = 0;
	info->phase = 1;
	info->level = 1;
	info->lines = 1;
	info->link_amnt = 0;
	info->max_paths = INT_MAX;
	info->path_saved = 0;
	info->rooms_to_check = (char**)malloc(sizeof(char*) * 1);
	info->rooms_to_check[0] = NULL;
	info->round = 0;
	info->required = 0;
	info->accurate = 0;
}

/*
**	Very highly useful dispatcher function.
*/

static void		lem_in_dispatcher(t_info *info)
{
	get_links(info);
	second_round(info);
	third_round(info);
	sort_paths(info);
	if (info->flag_storage & PATHS)
	{
		ft_printf("\nants: %d\n\nPATHS  SAVED:\n\n", info->ants);
		print_paths(info);
	}
	else
		write(1, "\n", 1);
	ant_flow(info);
}

static void		lem_in(int ac, char *av, t_info *info)
{
	char		*line;
	t_output	*output;

	if (!(output = (t_output*)malloc(sizeof(t_output))))
		exit_error(ERR_MALLOC, info);
	if (ac > 1)
		av[0] += 0;
	info->fd = 0;
	init_info(info);
	if (!(get_next_line(info->fd, &line)))
		exit_error(ERR_NO_MAP, info);
	output->line = ft_strdup(line);
	parse_ants(info, output);
	free(line);
	parse_map(output, info);
	if (info->start_end_link)
		all_ants_to_end_at_once(info);
	else
		lem_in_dispatcher(info);
	if (info->flag_storage & LINES)
		ft_printf(BOLD_RED "\nlines required: %d\nlines: %d (%+d)\n" RESET,
		info->required, info->lines, info->lines - info->required);
	lst_free(output);
}

int				main(int ac, char **av)
{
	t_info		*info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit_error_no_info(ERR_MALLOC);
	parse_flags(ac, av, info);
	if (ac > 0 && !(info->flag_storage & HELP))
	{
		if (info->flag_storage & VERBOSE)
			ft_printf(BOLD_MAGENTA "Verbose mode activated!\n" RESET);
		lem_in(ac, av[1], info);
	}
	else if (info->flag_storage & HELP)
		help_print();
	else
		exit_error(ERR_USAGE, info);
	if (info->flag_storage & LEAKS)
		system("leaks lem-in");
	return (0);
}
