/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:46:25 by elindber          #+#    #+#             */
/*   Updated: 2020/01/15 18:46:52 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags	*print_c(t_tags *ids)
{
	char	c;

	c = (char)va_arg(ids->arguments, int);
	if (ids->minwth > 0 && ids->current_flag[4] == '\0')
		minwth_print(ids, 1);
	write(1, &c, 1);
	ids->printed_chars++;
	if (ids->minwth > 0 && ids->current_flag[4] != '\0')
		minwth_print(ids, 1);
	return (ids);
}
