/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:50:24 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/27 15:37:35 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Int check for ant input plus checking that it is not a room name.
*/

int			ft_isint(char *str)
{
	while (ft_isdigit(*str))
	{
		str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

/*
**	Validating and reading the first line.
*/

void		parse_ants(t_info *info, t_output *output)
{
	if (ft_isint(output->line))
	{
		if (!(info->flag_storage & ANTS))
		{
			info->ants = ft_atoi(output->line);
			if (info->ants < 1)
				exit_error(ERR_ANTS, info);
		}
		info->ants_at_start = info->ants;
	}
	else
		exit_error(ERR_ANTS, info);
}
