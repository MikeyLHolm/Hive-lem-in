/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:37:29 by elindber          #+#    #+#             */
/*   Updated: 2020/01/28 11:18:56 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags			*print_s(t_tags *ids)
{
	char	*str;
	size_t	len;

	str = va_arg(ids->arguments, char*);
	if (str == NULL)
		str = "(null)";
	if (ids->period == 1 && ids->maxwth < ft_strlen(str))
		str = ft_strsub(str, 0, ids->maxwth);
	else
		str = ft_strsub(str, 0, ft_strlen(str));
	len = ft_strlen(str);
	if (ids->minwth > 0 && ids->current_flag[4] == '\0'
		&& ids->current_flag[1] == '\0')
		minwth_print(ids, len);
	if (ids->current_flag[1] == '0' && len < ids->minwth)
		put_zero_df(ids, len);
	ft_putstr(str);
	ids->printed_chars += len;
	if (ids->minwth > 0 && ids->current_flag[4] == '-')
		minwth_print(ids, len);
	free(str);
	return (ids);
}
