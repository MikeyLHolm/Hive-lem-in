/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 12:06:54 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/21 16:36:07 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		exit_error_no_info(const char *str)
{
	// (void)str;
	// ft_putendl_fd("ERROR", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void		exit_error(const char *str, t_info *info)
{
	if (info->flags->error)
		ft_putendl_fd(str, 2);
	else
	{
		(void)str;
		ft_putendl_fd("ERROR", 2);
	}
	exit(1);
}
