/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:43:42 by elindber          #+#    #+#             */
/*   Updated: 2019/11/12 18:27:56 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	t;

	i = 0;
	t = 0;
	if (needle[t] == '\0')
		return ((char*)(haystack));
	while (haystack[i])
	{
		t = 0;
		while (haystack[i + t] == needle[t] && ((i + t) < len))
		{
			t++;
			if (needle[t] == '\0')
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
