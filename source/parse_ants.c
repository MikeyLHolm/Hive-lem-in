/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:50:24 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/14 18:04:37 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/lem_in.h"

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
**	Add <1 check to atoi or isint?
*/

void		parse_ants(t_info *info, t_output *output)
{
	if (ft_isint(output->line))
	{
		info->ants = ft_atoi(output->line);
		if (info->ants < 1)
			exit_error(ERR_ANTS);
		info->ants_at_start = info->ants;
	}
	else
		exit_error(ERR_ANTS);
}