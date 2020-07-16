/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:09:00 by elindber          #+#    #+#             */
/*   Updated: 2020/01/24 12:33:22 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags		*print_percent(t_tags *ids)
{
	if (ids->current_flag[4] == '-')
		write(1, "%", 1);
	while (ids->minwth > 1 && ids->current_flag[1] != '0')
	{
		write(1, " ", 1);
		ids->minwth--;
		ids->printed_chars++;
	}
	while (ids->minwth > 1 && ids->current_flag[1] == '0')
	{
		write(1, "0", 1);
		ids->minwth--;
		ids->printed_chars++;
	}
	if (ids->current_flag[4] != '-')
		write(1, "%", 1);
	ids->printed_chars++;
	return (ids);
}
