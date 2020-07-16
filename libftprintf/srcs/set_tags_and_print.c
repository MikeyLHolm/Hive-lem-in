/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tags_and_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:34:36 by elindber          #+#    #+#             */
/*   Updated: 2020/01/28 12:48:59 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags			*read_arg_type(t_tags *ids)
{
	if (ids->current_type == 'c')
		print_c(ids);
	if (ids->current_type == 's')
		print_s(ids);
	if (ids->current_type == 'p')
		print_p(ids);
	if (ids->current_type == 'd' || ids->current_type == 'i')
		print_d(ids);
	if (ids->current_type == '%')
		print_percent(ids);
	if (ids->current_type == 'o')
		print_o(ids);
	if (ids->current_type == 'u')
		print_u(ids);
	if (ids->current_type == 'x' || ids->current_type == 'X')
		print_x(ids);
	if (ids->current_type == 'f')
		print_f(ids);
	return (ids);
}

static t_tags	*call_identifier_readers(t_tags *ids)
{
	ids->i++;
	create_tmp_ids(ids);
	scan_flags(ids);
	scan_minwth(ids);
	scan_period_maxwth(ids);
	scan_modifier(ids);
	scan_arg_type(ids);
	read_arg_type(ids);
	return (ids);
}

int				read_format(t_tags *ids)
{
	while (ids->format[ids->i])
	{
		if (ids->format[ids->i] == '%' && ids->format[ids->i + 1] == '%')
		{
			write(1, &ids->format[ids->i], 1);
			ids->i += 2;
			ids->printed_chars++;
		}
		else if (ids->format[ids->i] == '%')
			call_identifier_readers(ids);
		else
		{
			write(1, &ids->format[ids->i], 1);
			ids->printed_chars++;
			ids->i++;
		}
	}
	return (0);
}
