/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:05:35 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/21 13:25:54 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		init_flags(t_info *info)
{
	t_flags		*flags;

	if (!(flags = (t_flags*)malloc(sizeof(t_flags))))
		exit_error(ERR_MALLOC, info);
	info->flags = flags;
	info->ants = -1;
	info->flags->ants = 0;
	info->flags->error = 0;
	info->flags->help = 0;
	info->flags->lines = 0;
	info->flags->paths = 0;
	info->flags->verbose = 0;
}

void		parse_flags(int ac, char **av, t_info *info)
{
	init_flags(info);
	// maybe strchr here...
	while (ac-- > 1 && (!ft_strcmp(av[1], "-a") || !ft_strcmp(av[1], "-e") ||
					!ft_strcmp(av[1], "-h") || !ft_strcmp(av[1], "-l") ||
					!ft_strcmp(av[1], "-p") || !ft_strcmp(av[1], "-p")))
	{
		if (ft_strequ(av[1], "-e"))
			info->flags->error = 1;
		else if (ft_strequ(av[1], "-h"))
			info->flags->help = 1;
		else if (ft_strequ(av[1], "-l"))
			info->flags->lines = 1;
		else if (ft_strequ(av[1], "-p"))
			info->flags->paths = 1;
		else if (ft_strequ(av[1], "-v"))
			info->flags->verbose = 1;
		else if (ft_strequ(av[1], "-a"))
		{
			info->flags->ants = 1;
			av++;
			ac--;
			info->ants = ft_atoi(av[1]);
		}
		av++;
	}
}
