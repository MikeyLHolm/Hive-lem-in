/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:31:19 by elindber          #+#    #+#             */
/*   Updated: 2020/01/20 19:24:24 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long double	cast_double(t_tags *ids, long double nbr)
{
	if (ft_strcmp(ids->current_modifier, "\0") == 0)
		nbr = (double)va_arg(ids->arguments, double);
	if (ft_strcmp(ids->current_modifier, "l") == 0)
		nbr = (double)va_arg(ids->arguments, double);
	if (ft_strcmp(ids->current_modifier, "L") == 0)
		nbr = (long double)va_arg(ids->arguments, long double);
	if (nbr < 0)
		ids->negative = -1;
	return ((long double)nbr);
}

intmax_t	cast_number(t_tags *ids, intmax_t nbr)
{
	if (ft_strcmp(ids->current_modifier, "\0") == 0)
		nbr = (int)va_arg(ids->arguments, int);
	if (ft_strcmp(ids->current_modifier, "h") == 0)
		nbr = (short)va_arg(ids->arguments, int);
	if (ft_strcmp(ids->current_modifier, "l") == 0)
		nbr = (long)va_arg(ids->arguments, long int);
	if (ft_strcmp(ids->current_modifier, "hh") == 0)
		nbr = (signed char)va_arg(ids->arguments, int);
	if (ft_strcmp(ids->current_modifier, "ll") == 0)
		nbr = (long long)va_arg(ids->arguments, long long int);
	if (nbr < 0)
		ids->negative = -1;
	return ((intmax_t)nbr);
}

uintmax_t	cast_unsigned_number(t_tags *ids, uintmax_t nbr)
{
	if (ft_strcmp(ids->current_modifier, "\0") == 0)
		nbr = (unsigned int)va_arg(ids->arguments, unsigned int);
	if (ft_strcmp(ids->current_modifier, "h") == 0)
		nbr = (unsigned short)va_arg(ids->arguments, unsigned int);
	if (ft_strcmp(ids->current_modifier, "l") == 0)
		nbr = (unsigned long)va_arg(ids->arguments, unsigned long int);
	if (ft_strcmp(ids->current_modifier, "hh") == 0)
		nbr = (unsigned char)va_arg(ids->arguments, unsigned int);
	if (ft_strcmp(ids->current_modifier, "ll") == 0)
		nbr = (unsigned long long)
		va_arg(ids->arguments, unsigned long long int);
	return ((uintmax_t)nbr);
}
