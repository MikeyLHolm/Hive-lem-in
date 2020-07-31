/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 10:05:35 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/30 15:28:53 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			help_print(void)
{
	ft_putendl("|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|");
	ft_putendl("|       Welcome to Lem_in & how to use it !!!               |");
	ft_putendl("|___________________________________________________________|");
	ft_putendl("| Available flags:                                          |");
	ft_putendl("|                                                           |");
	ft_putendl("| -a |	Insert number of ants manually   [./lem-in -a 100]  |");
	ft_putendl("| -e |	Improved error management                           |");
	ft_putendl("| -h |	Show options and other relevant info                |");
	ft_putendl("| -l |	Show amount of used lines                           |");
	ft_putendl("| -p |	Show found paths                                    |");
	ft_putendl("| -v |	Activate verbose mode                               |");
	ft_putendl("| -x |	Check for leaks                                     |");
	ft_putendl("|___________________________________________________________|");
	ft_putendl("| Usage:                                                    |");
	ft_putendl("|                                                           |");
	ft_putendl("|       ./lem-in [possible flags] < [map]                   |");
	ft_putendl("|       ./generator --flow-one | ./lem-in                   |");
	ft_putendl("|       ./generator --flow-ten | ./lem-in                   |");
	ft_putendl("|       ./generator --flow-thousand | ./lem-in              |");
	ft_putendl("|       ./generator --big | ./lem-in                        |");
	ft_putendl("|       ./generator --big-superposition | ./lem-in          |");
	ft_putendl("|                                                           |");
	ft_putendl("|       ./run_map.sh -x [number of runs]                    |");
	ft_putendl("|___________________________________________________________|");
}

static void		save_flag(t_info *info, char flag)
{
	if (flag == 'a')
		info->flag_storage = info->flag_storage | ANTS;
	else if (flag == 'e')
		info->flag_storage = info->flag_storage | ERROR;
	else if (flag == 'h')
		info->flag_storage = info->flag_storage | HELP;
	else if (flag == 'l')
		info->flag_storage = info->flag_storage | LINES;
	else if (flag == 'p')
		info->flag_storage = info->flag_storage | PATHS;
	else if (flag == 'v')
		info->flag_storage = info->flag_storage | VERBOSE;
	else if (flag == 'x')
		info->flag_storage = info->flag_storage | LEAKS;
}

void			parse_flags(int ac, char **av, t_info *info)
{
	int			i;

	info->ants = -1;
	info->flag_storage = 0;
	while (ac > 1 && av[1] && av[1][0] == '-')
	{
		i = 1;
		while (av[1][i] && ft_strchr("aehlpvx", av[1][i]))
			save_flag(info, av[1][i++]);
		av++;
	}
	if (info->flag_storage & ANTS)
		info->ants = ft_atoi(av[1]);
}
