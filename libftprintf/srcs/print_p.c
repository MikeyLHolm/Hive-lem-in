/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:42:03 by elindber          #+#    #+#             */
/*   Updated: 2020/01/24 17:18:57 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags			*print_p(t_tags *ids)
{
	uintmax_t	ptr;
	char		*str;

	ptr = (unsigned long)va_arg(ids->arguments, unsigned long int);
	str = imaxtoa_base(ptr, 16);
	if (ids->minwth > 0 && ids->current_flag[4] != '-')
		minwth_print(ids, ft_strlen(str) + 2);
	ft_putstr("0x");
	if (ids->period == 1 && ids->maxwth == 0 && ptr == 0)
	{
		ids->printed_chars += 2;
		period_zero(ids);
		return (ids);
	}
	if ((ids->current_flag[1] == '0' && ft_strlen(str) + 2 < ids->minwth &&
	ids->minwth > 0) || (ids->period == 1 && ids->maxwth > ft_strlen(str)))
		put_zero_p(ids, ft_strlen(str));
	ft_putstr(str);
	ids->printed_chars += ft_strlen(str) + 2;
	if (ids->current_flag[4] == '-' && ((ids->maxwth >= ft_strlen(str) + 2
	&& ids->period == 1) || ids->minwth > 0))
		minwth_print(ids, ft_strlen(str) + 2);
	free(str);
	return (ids);
}
