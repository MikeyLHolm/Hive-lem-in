/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 09:47:30 by elindber          #+#    #+#             */
/*   Updated: 2019/11/12 19:42:23 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_iswhtspc(int c)
{
	if (c == 9 || c == 10 || c == 32)
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		end;
	char	*trim;

	if (!s)
		return (NULL);
	i = (int)(ft_strlen(s) - 1);
	while (ft_iswhtspc(s[i]))
		i--;
	end = i + 1;
	if (end == 0)
	{
		if (!(trim = ft_strnew((size_t)end)))
			return (NULL);
		return (trim);
	}
	i = 0;
	while (ft_iswhtspc(s[i]))
		i++;
	if (!(trim = ft_strsub(s, i, (size_t)(end - i))))
		return (NULL);
	return (trim);
}
