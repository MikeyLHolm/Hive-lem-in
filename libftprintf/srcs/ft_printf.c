/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:14:39 by elindber          #+#    #+#             */
/*   Updated: 2020/01/21 16:56:45 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags	*set_ids(t_tags *ids)
{
	ids->i = 0;
	ids->printed_chars = 0;
	ids->flag = "#0 +-";
	ids->arg_type = "%cCspdDiouxXf";
	ids->modifiers = "hlL";
	return (ids);
}

t_tags	*create_tmp_ids(t_tags *ids)
{
	ids->minwth = 0;
	ids->period = 0;
	ids->maxwth = 0;
	ids->negative = 1;
	ids->double_len = 0;
	ids->current_type = '\0';
	ids->current_flag[0] = '\0';
	ids->current_flag[1] = '\0';
	ids->current_flag[2] = '\0';
	ids->current_flag[3] = '\0';
	ids->current_flag[4] = '\0';
	ids->current_flag[5] = '\0';
	ids->current_modifier[0] = '\0';
	ids->current_modifier[1] = '\0';
	ids->current_modifier[2] = '\0';
	return (ids);
}

int		ft_printf(const char *format, ...)
{
	t_tags	*ids;

	if (!(ids = (t_tags*)malloc(sizeof(t_tags))))
		return (-1);
	ids->format = format;
	set_ids(ids);
	if (format)
	{
		va_start(ids->arguments, format);
		read_format(ids);
		va_end(ids->arguments);
	}
	free(ids);
	return (ids->printed_chars);
}
