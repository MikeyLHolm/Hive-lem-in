/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:03:23 by elindber          #+#    #+#             */
/*   Updated: 2019/11/12 19:02:45 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;
	unsigned int	index;

	if (!s)
		return (NULL);
	sub = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	index = 0;
	if (!sub || start > ft_strlen(s))
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		sub[index] = s[start];
		index++;
		start++;
		i++;
	}
	sub[index] = '\0';
	return (sub);
}
