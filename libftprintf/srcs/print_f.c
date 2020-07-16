/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:06:30 by elindber          #+#    #+#             */
/*   Updated: 2020/01/28 11:29:47 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static long double	approximize_nbr(t_tags *ids, long double nbr)
{
	long double		factor;
	size_t			count;

	factor = ids->maxwth == 0 && ids->period == 1 ? 0.499 : 0.500;
	count = ids->maxwth == 0 ? 6 : ids->maxwth;
	if (ids->period == 1 && ids->maxwth == 0)
		count = 0;
	while (count > 0 && count--)
		factor /= 10;
	nbr += factor;
	return (nbr);
}

static t_tags		*print_space_flag(t_tags *ids, size_t len)
{
	if (ids->current_flag[2] == ' ' && ids->current_flag[4] != '-' &&
	ids->period > 0 && ids->negative < 0 && len + ids->maxwth + 2 < ids->minwth)
	{
		write(1, " ", 1);
		ids->printed_chars++;
	}
	else if (ids->current_flag[2] == ' ' && ((ids->current_flag[4] != '-'
	&& ids->negative == 1) || (ids->period == 1 && ids->negative == 1
	&& len + ids->maxwth + 1 < ids->minwth)))
	{
		write(1, " ", 1);
		ids->printed_chars++;
	}
	else if (ids->current_flag[2] == ' ' && ((ids->current_flag[4] == '-'
	&& ids->negative == 1) || (ids->period == 1 && ids->negative == 1)))
	{
		write(1, " ", 1);
		ids->printed_chars++;
	}
	return (ids);
}

static t_tags		*print_front(t_tags *ids, long double nbr)
{
	intmax_t	casted;
	size_t		len;
	char		*front;

	casted = (long long)nbr;
	front = imaxtoa_base(casted, 10);
	len = ft_strlen(front);
	print_space_flag(ids, len);
	if (ids->current_flag[4] != '-' &&
	((ids->period == 0 && len + 7 < ids->minwth)
	|| (len + 1 + ids->maxwth < ids->minwth)))
		minwth_print(ids, len);
	if (ids->current_flag[1] == '0' && len < ids->minwth)
		put_zero_df(ids, len);
	if (ids->negative == -1 && ids->current_flag[3] != '+')
	{
		write(1, "-", 1);
		ids->printed_chars++;
	}
	if (ids->current_flag[3] == '+')
		put_plusminus(ids, ids->negative);
	ft_putstr(front);
	ids->printed_chars += len;
	free(front);
	return (ids);
}

static t_tags		*print_decimals(t_tags *ids, long double nbr, size_t count)
{
	uintmax_t	casted;

	nbr *= 10;
	casted = (uintmax_t)nbr;
	ft_putnbr(casted);
	ids->printed_chars++;
	ids->double_len++;
	nbr -= casted;
	if (count > 1)
		print_decimals(ids, nbr, count - 1);
	return (ids);
}

t_tags				*print_f(t_tags *ids)
{
	long double	nbr;

	nbr = cast_double(ids, 0);
	nbr = nbr * ids->negative;
	nbr = approximize_nbr(ids, nbr);
	print_front(ids, nbr);
	if (ids->maxwth > 0 || (ids->maxwth == 0 && ids->period == 0))
	{
		write(1, ".", 1);
		ids->printed_chars++;
		print_decimals
(ids, nbr - (long long)nbr, ids->maxwth == 0 ? 6 : ids->maxwth);
	}
	else if (ids->current_flag[0] == '#' && ids->period == 1
	&& ids->maxwth == 0)
	{
		write(1, ".", 1);
		ids->printed_chars++;
	}
	if (ids->current_flag[4] == '-' &&
	((ids->period == 0 && ids->double_len + 7 < ids->minwth) ||
	(ids->double_len + 1 + ids->maxwth < ids->minwth)))
		minwth_print(ids, ids->double_len);
	return (ids);
}
