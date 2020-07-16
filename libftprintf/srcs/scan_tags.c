/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:35:37 by elindber          #+#    #+#             */
/*   Updated: 2020/01/17 16:43:02 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_tags	*scan_arg_type(t_tags *ids)
{
	int	i;

	i = 0;
	while (ids->arg_type[i])
	{
		if (ids->format[ids->i] == ids->arg_type[i])
		{
			ids->current_type = ids->format[ids->i];
			ids->i++;
			return (ids);
		}
		i++;
	}
	return (ids);
}

t_tags	*scan_modifier(t_tags *ids)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (ids->format[ids->i] == 'h' || ids->format[ids->i] == 'l' ||
		ids->format[ids->i] == 'L')
	{
		while (ids->modifiers[i] != '\0')
		{
			while (ids->modifiers[i] == ids->format[ids->i])
			{
				ids->current_modifier[c] = ids->format[ids->i];
				if (c < 1)
					c++;
				ids->i++;
			}
			i++;
		}
	}
	return (ids);
}

t_tags	*scan_period_maxwth(t_tags *ids)
{
	if (ids->format[ids->i] == '.')
	{
		ids->period++;
		ids->i++;
		while (ids->format[ids->i] >= '0' && ids->format[ids->i] <= '9')
		{
			ids->maxwth += ids->format[ids->i] - 48;
			if (ids->format[ids->i + 1] >= '0' &&
				ids->format[ids->i + 1] <= '9')
				ids->maxwth = ids->maxwth * 10;
			ids->i++;
		}
	}
	return (ids);
}

t_tags	*scan_minwth(t_tags *ids)
{
	while (ids->format[ids->i] >= '0' && ids->format[ids->i] <= '9')
	{
		ids->minwth += ids->format[ids->i] - 48;
		if (ids->format[ids->i + 1] >= '0' && ids->format[ids->i + 1] <= '9')
			ids->minwth = ids->minwth * 10;
		ids->i++;
	}
	return (ids);
}

t_tags	*scan_flags(t_tags *ids)
{
	int		i;

	i = 0;
	while (ids->flag[i] != '\0')
	{
		while (ids->flag[i] == ids->format[ids->i])
		{
			while (ids->format[ids->i] == '#' && ids->i++)
				ids->current_flag[0] = '#';
			while (ids->format[ids->i] == '0' && ids->i++)
				ids->current_flag[1] = '0';
			while (ids->format[ids->i] == ' ' && ids->i++)
				ids->current_flag[2] = ' ';
			while (ids->format[ids->i] == '+' && ids->i++)
				ids->current_flag[3] = '+';
			while (ids->format[ids->i] == '-' && ids->i++)
				ids->current_flag[4] = '-';
			i = 0;
		}
		i++;
	}
	return (ids);
}
