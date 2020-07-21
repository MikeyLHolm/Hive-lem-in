/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:26:57 by elindber          #+#    #+#             */
/*   Updated: 2020/07/21 12:58:51 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			free_memory(t_info *info, int i)
{
	free(info->start);
	free(info->end);
	while (info->rooms[i] != NULL)
	{
		free(info->rooms[i]->name);
		i++;
	}
	free_2d_array(info->paths);
}

void			free_2d_array(char **arr)
{
	int				i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void			init_info(t_info *info)
{
	int i;

	i = 0;
	while (i < 513)
		info->tmp_string[i++] = EMPTY;
	if (!info->flags->ants)
		info->ants = -1;
	info->ants_at_start = 0;
	info->ants_at_end = 0;
	info->path_amount_1 = 0;
	info->path_amount_2 = 0;
	info->phase = 1;
	info->level = 1;
	info->lines = 1;
	info->link_amnt = 0;
	info->max_paths = INT_MAX;
	info->path_saved = 0;
	info->path_stack = 0;
	info->rooms_to_check = (char**)malloc(sizeof(char*) * 1);
	info->rooms_to_check[0] = NULL;
}

void	print_paths(t_info *info)
{
	int				i;

	i = 0;
	while (info->valid_paths[i] != NULL)
	{
		ft_printf("[%s]\n", ft_strtrim(info->valid_paths[i]));
		i++;
	}
	ft_putchar('\n');
	if (info->path_amount_2 > 0)
	{
		i = 0;
		ft_printf("OR\n");
		while (info->valid_paths_2[i] != NULL)
		{
			ft_printf("[%s]\n", ft_strtrim(info->valid_paths_2[i]));
			i++;
		}
	}
	ft_putchar('\n');
}

void	second_round(t_info *info)
{
	int		i;

	i = 0;
	info->phase = 2;
	info->level = 1;
	reset_tmp_stacks(info);
	while (info->rooms[i] != NULL)
	{
		info->rooms[i]->visited = 0;
		i++;
	}
	get_links_for_start(info);
	find_paths(info);
}

static void		lem_in(int ac, char *av, t_info *info)
{
	t_ant			*ant;
	t_link			*link;
	t_output		*output;
	char			*line;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		exit_error(ERR_MALLOC, info);
	if (!(link = (t_link*)malloc(sizeof(t_link))))
		exit_error(ERR_MALLOC, info);
	if (!(output = (t_output*)malloc(sizeof(t_output))))
		exit_error(ERR_MALLOC, info);
	if (ac > 1)
	{
		ac += 0;
		av[0] += 0;
	}
	info->tmpfd = 0;
//	info->tmpfd = open(av, O_RDONLY);
	init_info(info);
	get_next_line(info->tmpfd, &line);
	output->line = ft_strdup(line);
	parse_ants(info, output);
	free(line);
	if (!parse_v2(output, info))
		exit_error(ERR_PARSE_V2, info);
	get_links(info);
	second_round(info);
	ft_printf("><><><><><><\n><><><><><><\nants: %d\nPATHS  SAVED:\n", info->ants);
	print_paths(info);
	//write(1, "\n", 1);
	ant_flow(info);
	ft_printf("lines: %d\n", info->lines);
//	free_memory(info, 0);
}

int				main(int ac, char **av)
{
	t_info			*info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit_error_no_info(ERR_MALLOC);
	parse_flags(ac, av, info);
	if (ac > 0 && !info->flags->help)
	{
		if (info->flags->verbose)
			ft_printf("Verbose mode activated!\n");
		lem_in(ac, av[1], info);
	}
	else if (info->flags->help)
		ft_printf("HELP!\n");
	else
		exit_error(ERR_USAGE, info);
//	while (1);
	return (0);
}
