/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:52:19 by elindber          #+#    #+#             */
/*   Updated: 2019/11/12 18:26:57 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char*)(s1);
	str2 = (unsigned char*)(s2);
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && str1[i] != '\0' && i + 1 < n)
		i++;
	return (str1[i] - str2[i]);
}
