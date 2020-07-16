/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:29:17 by elindber          #+#    #+#             */
/*   Updated: 2019/11/12 19:03:09 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	int		x;
	char	*joint;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	x = 0;
	if (!(joint = ft_strnew(a + b)))
		return (NULL);
	joint = ft_strcpy(joint, s1);
	while (x < b)
	{
		joint[a + x] = s2[x];
		x++;
	}
	return (joint);
}
