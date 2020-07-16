/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:47:32 by elindber          #+#    #+#             */
/*   Updated: 2020/01/24 17:08:54 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_tags	*hashtag_puts_0x(t_tags *ids, uintmax_t nbr)
{
	if (nbr == 0)
		return (ids);
	if (ids->current_type == 'x')
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
	ids->printed_chars += 2;
	return (ids);
}

static t_tags	*prefix_print(t_tags *ids, uintmax_t nbr, size_t len)
{
	if (nbr == 0 && ids->current_flag[0] == '#' && ids->current_flag[4] != '-')
		minwth_print(ids, len - 2);
	else if (ids->minwth > len && ids->current_flag[4] != '-' &&
	ids->current_flag[1] != '0')
		minwth_print(ids, len);
	else if (ids->current_flag[1] == '0' && ids->minwth > len
	&& ids->current_flag[4] != '-' && ids->period == 1)
		minwth_print(ids, len);
	if (ids->current_flag[0] == '#')
		hashtag_puts_0x(ids, nbr);
	if (ids->current_flag[1] == '0' || (ids->period == 1 && ids->maxwth > len))
		put_zero_oxu(ids, len);
	return (ids);
}

t_tags			*print_x(t_tags *ids)
{
	uintmax_t	nbr;
	size_t		len;
	char		*str;

	nbr = cast_unsigned_number(ids, 0);
	str = ids->current_type == 'x' ? uimaxtoa_base(nbr, 16)
	: uimaxtoa_base_capital(nbr, 16);
	len = ft_strlen(str);
	if (ids->period == 1 && ids->maxwth == 0 && nbr == 0)
	{
		period_zero(ids);
		return (ids);
	}
	prefix_print(ids, nbr, len);
	ft_putstr(str);
	ids->printed_chars += len;
	if (nbr == 0 && ids->current_flag[0] == '#' && ids->current_flag[4] == '-')
		minwth_print(ids, len - 2);
	else if (ids->minwth > 0 && ids->current_flag[4] == '-')
		minwth_print(ids, len);
	free(str);
	return (ids);
}
