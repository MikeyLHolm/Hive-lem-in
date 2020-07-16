/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:11:28 by elindber          #+#    #+#             */
/*   Updated: 2020/01/24 17:08:54 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_tags	*write_space_or_plus(t_tags *ids)
{
	if (ids->current_flag[3] == '+')
	{
		write(1, "+", 1);
		ids->printed_chars++;
	}
	else if (ids->current_flag[2] == ' ')
	{
		write(1, " ", 1);
		ids->printed_chars++;
	}
	return (ids);
}

t_tags			*period_zero(t_tags *ids)
{
	if (ids->minwth == 0 && ids->current_flag[2] == '\0'
	&& ids->current_flag[3] == '\0')
		return (ids);
	if (ids->minwth > 0 &&
	(ids->current_flag[2] == ' ' || ids->current_flag[3] == '+'))
		ids->minwth--;
	while (ids->minwth > 0 && ids->current_flag[4] != '-')
	{
		write(1, " ", 1);
		ids->minwth--;
		ids->printed_chars++;
	}
	write_space_or_plus(ids);
	while (ids->minwth > 0 && ids->current_flag[4] == '-')
	{
		write(1, " ", 1);
		ids->minwth--;
		ids->printed_chars++;
	}
	return (ids);
}

static t_tags	*prefix_print(t_tags *ids, size_t len)
{
	if (ids->minwth > len && ids->current_flag[4] != '-'
		&& ids->current_flag[1] != '0')
		minwth_print(ids, len);
	else if (ids->minwth > len && ids->current_flag[4] != '-'
	&& ids->current_flag[1] == '0' && ids->period == 1)
		minwth_print(ids, len);
	if ((ids->current_flag[1] == '0' && len < ids->minwth && ids->minwth > 0)
		|| (ids->period == 1 && ids->maxwth > len))
		put_zero_oxu(ids, len);
	return (ids);
}

t_tags			*print_u(t_tags *ids)
{
	uintmax_t	nbr;
	size_t		len;
	char		*str;

	nbr = cast_unsigned_number(ids, 0);
	str = uimaxtoa_base(nbr, 10);
	len = ft_strlen(str);
	if (ids->period == 1 && ids->maxwth == 0 && nbr == 0)
	{
		period_zero(ids);
		return (ids);
	}
	prefix_print(ids, len);
	ft_putstr(str);
	ids->printed_chars += len;
	if (ids->minwth > len && ids->current_flag[4] == '-')
		minwth_print(ids, len);
	free(str);
	return (ids);
}
