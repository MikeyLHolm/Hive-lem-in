/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 12:06:54 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/30 11:43:01 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Exit error function when t_info is not available.
**	Comment 2 first lines and add line below for more detailed error msg.
**		ft_putendl_fd(str, 2);
*/

void		exit_error_no_info(const char *str)
{
	(void)str;
	ft_putendl_fd("ERROR", 2);
	exit(1);
}

/*
**	Exit error with option for more detailed error management.
*/

void		exit_error(const char *str, t_info *info)
{
	if (info->flag_storage & ERROR)
		ft_putendl_fd(str, 2);
	else
	{
		(void)str;
		ft_putendl_fd("ERROR", 2);
	}
	exit(1);
}
