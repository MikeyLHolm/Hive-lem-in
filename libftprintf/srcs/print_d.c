/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:58:32 by elindber          #+#    #+#             */
/*   Updated: 2020/01/28 11:50:45 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags			*put_plusminus(t_tags *ids, intmax_t nbr)
{
	if (nbr < 0)
		write(1, "-", 1);
	if (nbr >= 0)
		write(1, "+", 1);
	ids->printed_chars++;
	return (ids);
}

static t_tags	*put_invisible_plus(t_tags *ids)
{
	if (ids->negative == 1 && ids->current_flag[3] == '\0')
	{
		write(1, " ", 1);
		ids->printed_chars++;
	}
	return (ids);
}

static t_tags	*prefix_print(t_tags *ids, size_t len, intmax_t d)
{
	if (ids->minwth > len && ids->current_flag[4] != '-'
	&& (ids->current_flag[1] != '0'
	|| (((ids->maxwth - len) + len < ids->minwth) && ids->maxwth > 0)))
		minwth_print(ids, len);
	else if (ids->minwth > len && ids->current_flag[4] != '-' &&
	ids->current_flag[1] == '0' && ids->period == 1 && ids->maxwth == 0)
		minwth_print(ids, len);
	if (ids->current_flag[2] == ' ' && ids->negative == 1
	&& ids->current_flag[3] != '+')
		put_invisible_plus(ids);
	if (ids->current_flag[3] == '+' || d < 0)
		put_plusminus(ids, d);
	if (ids->period == 1)
		put_zero_df(ids, len);
	return (ids);
}

t_tags			*print_d(t_tags *ids)
{
	intmax_t	nbr;
	intmax_t	len;
	char		*str;

	nbr = cast_number(ids, 0);
	len = base_nbrcount(nbr, 10);
	if (ids->period == 1 && ids->maxwth == 0 && nbr == 0)
	{
		period_zero(ids);
		return (ids);
	}
	prefix_print(ids, len, nbr);
	nbr *= ids->negative;
	if (ids->current_flag[1] != '\0' && ids->period == 0)
		put_zero_df(ids, len);
	str = imaxtoa_base(nbr, 10);
	ft_putstr(str);
	ids->printed_chars += ft_strlen(str);
	if (ids->minwth > 0 && ids->current_flag[4] == '-')
		minwth_print(ids, len);
	free(str);
	return (ids);
}
