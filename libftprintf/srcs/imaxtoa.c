/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imaxtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:25:38 by elindber          #+#    #+#             */
/*   Updated: 2020/04/30 14:28:14 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

intmax_t		unsigned_base_nbrcount(uintmax_t n, size_t base)
{
	intmax_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n = n / base;
	}
	return (i);
}

char			*uimaxtoa_base_capital(uintmax_t nbr, size_t base)
{
	char		*base_str;
	char		*str;
	intmax_t	count;

	base_str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	count = unsigned_base_nbrcount(nbr, base);
	if (!(str = ft_strnew(count)))
		return (NULL);
	count--;
	if (nbr == 0)
		str[0] = '0';
	while (nbr > 0)
	{
		str[count] = base_str[nbr % base];
		nbr /= base;
		count--;
	}
	return (str);
}

char			*uimaxtoa_base(uintmax_t nbr, size_t base)
{
	char		*base_str;
	char		*str;
	intmax_t	count;

	base_str = "0123456789abcdefghijklmnopqrstuvwxyz";
	count = unsigned_base_nbrcount(nbr, base);
	if (!(str = ft_strnew(count)))
		return (NULL);
	count--;
	if (nbr == 0)
		str[0] = '0';
	while (nbr > 0)
	{
		str[count] = base_str[nbr % base];
		nbr /= base;
		count--;
	}
	return (str);
}

intmax_t		base_nbrcount(intmax_t n, size_t base)
{
	intmax_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		i++;
		n = n / base;
	}
	return (i);
}

char			*imaxtoa_base(intmax_t nbr, size_t base)
{
	char		*base_str;
	char		*str;
	intmax_t	count;

	if (nbr == LONG_MIN || nbr == LLONG_MIN)
		return (ft_strdup("9223372036854775808"));
	base_str = "0123456789abcdefghijklmnopqrstuvwxyz";
	count = base_nbrcount(nbr, base);
	if (!(str = ft_strnew(count)))
		return (NULL);
	count--;
	if (nbr == 0)
		str[0] = '0';
	while (nbr > 0)
	{
		str[count] = base_str[nbr % base];
		nbr /= base;
		count--;
	}
	return (str);
}
