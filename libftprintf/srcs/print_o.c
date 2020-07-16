/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:03:01 by elindber          #+#    #+#             */
/*   Updated: 2020/01/24 17:08:54 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_tags		*period_zero_check(t_tags *ids)
{
	if (ids->minwth == 0 && ids->current_flag[0] == '#')
	{
		write(1, "0", 1);
		ids->printed_chars++;
	}
	period_zero(ids);
	return (ids);
}

static t_tags		*hashtag_puts_zero(t_tags *ids, uintmax_t nbr, size_t len)
{
	if (nbr == 0 || (ids->period == 1 && ids->maxwth > len))
		return (ids);
	write(1, "0", 1);
	ids->printed_chars++;
	return (ids);
}

static t_tags		*prefix_print(t_tags *ids, uintmax_t nbr, size_t len)
{
	if (nbr == 0 && ids->current_flag[0] == '#' && ids->current_flag[4] != '-')
		minwth_print(ids, len - 1);
	else if (ids->minwth > len && ids->current_flag[4] != '-' &&
	ids->current_flag[1] != '0')
		minwth_print(ids, len);
	else if (ids->current_flag[1] == '0' && ids->minwth > len
	&& ids->current_flag[4] != '-' && ids->period == 1)
		minwth_print(ids, len);
	if (ids->current_flag[0] == '#')
		hashtag_puts_zero(ids, nbr, len);
	if (ids->current_flag[1] == '0' || (ids->period == 1 && ids->maxwth > len))
		put_zero_oxu(ids, len);
	return (ids);
}

t_tags				*print_o(t_tags *ids)
{
	uintmax_t	nbr;
	size_t		len;
	char		*str;

	nbr = cast_unsigned_number(ids, 0);
	str = uimaxtoa_base(nbr, 8);
	len = ft_strlen(str);
	if (ids->period == 1 && ids->maxwth == 0 && nbr == 0)
	{
		period_zero_check(ids);
		return (ids);
	}
	prefix_print(ids, nbr, len);
	ft_putstr(str);
	ids->printed_chars += len;
	if (nbr == 0 && ids->current_flag[0] == '#' && ids->current_flag[4] == '-')
		minwth_print(ids, len - 1);
	else if (ids->minwth > 0 && ids->current_flag[4] == '-')
		minwth_print(ids, len);
	free(str);
	return (ids);
}
