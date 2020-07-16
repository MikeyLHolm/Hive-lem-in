/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minwth_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:33:48 by elindber          #+#    #+#             */
/*   Updated: 2020/01/28 11:39:33 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	mod_len_dbl(t_tags *ids, size_t len)
{
	if (ids->period == 0)
		len += 7;
	if (ids->period == 1 && ids->maxwth > 0)
		len += ids->maxwth + 1;
	if (ids->current_flag[1] == '0')
		len += ids->minwth;
	if (ids->negative == -1 || ids->current_flag[3] == '+')
		len++;
	if (ids->current_flag[4] == '-' && ids->period == 1 && ids->maxwth == 0)
		len++;
	if (ids->current_flag[4] == '-' && ids->period == 1 && ids->maxwth == 0
	&& ids->current_flag[2] == ' ' && ids->negative == -1)
		len--;
	if (ids->current_flag[2] == ' ' && ids->current_flag[4] == '-'
	&& ids->negative == 1)
		len++;
	else if (ids->current_flag[2] == ' ' && ids->current_flag[4] == '-'
	&& ids->negative == -1 && ids->period == 1 && ids->maxwth == 0)
		len++;
	else if (ids->current_flag[2] == ' ' && ids->current_flag[4] != '-')
		len++;
	return (len);
}

static size_t	mod_len_oct_udec_hexa(t_tags *ids, size_t len)
{
	if (ids->maxwth > len && ids->current_flag[4] != '-')
		len += ids->maxwth - len;
	if (ids->current_flag[0] == '#'
	&& (ids->current_type == 'x' || ids->current_type == 'X'))
		len += 2;
	else if (ids->current_flag[0] == '#')
		len++;
	return (len);
}

static size_t	mod_len_ptr(t_tags *ids, size_t len)
{
	if (ids->current_flag[1] == '0' && ids->period == 0)
		return (len += ids->minwth);
	if (ids->period == 1 && ids->maxwth >= len - 2)
		len += (ids->maxwth - len) + 2;
	return (len);
}

static size_t	mod_len_int_char(t_tags *ids, size_t len, size_t og_len)
{
	if ((ids->current_flag[3] == '+' || ids->current_flag[2] == ' ') &&
		ids->negative == 1)
		len++;
	if (ids->negative == -1 && ids->maxwth > len && ids->current_flag[4] != '-')
		len++;
	else if (ids->negative == -1 && ids->maxwth >= og_len &&
	ids->current_flag[4] != '-' && ids->current_flag[1] == '0')
		len += 2;
	if (ids->maxwth >= og_len && ids->current_flag[4] != '-')
	{
		len += ids->maxwth - og_len;
		if (ids->current_flag[1] == '0' && ids->negative == -1
		&& ids->maxwth == og_len)
			len--;
		else if (ids->negative == -1 && ids->maxwth == og_len)
			len++;
	}
	return (len);
}

t_tags			*minwth_print(t_tags *ids, size_t len)
{
	size_t		og_len;

	og_len = len;
	if (ids->current_type == 'd' || ids->current_type == 'i'
	|| ids->current_type == 'c')
		len = mod_len_int_char(ids, len, og_len);
	if (ids->current_type == 'p')
		len = mod_len_ptr(ids, len);
	if (ids->current_type == 'o' || ids->current_type == 'u'
	|| ids->current_type == 'x' || ids->current_type == 'X')
		len = mod_len_oct_udec_hexa(ids, len);
	if (ids->current_type == 'f')
		len = mod_len_dbl(ids, len);
	while (ids->minwth > len)
	{
		write(1, " ", 1);
		ids->printed_chars++;
		len++;
	}
	return (ids);
}
