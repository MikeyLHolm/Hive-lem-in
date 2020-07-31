/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:47:57 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 19:08:34 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static int	rest_of_line(char **str, char **line)
{
	size_t		i;
	char		*next;

	i = 0;
	while (str[0][i] != '\n' && str[0][i] != '\0')
		i++;
	if (str[0][i] == '\n')
	{
		*line = ft_strsub(str[0], 0, i);
		next = ft_strdup(str[0] + (i + 1));
		free(str[0]);
		str[0] = next;
	}
	else
	{
		*line = ft_strsub(str[0], 0, i);
		ft_strdel(&str[0]);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*str[MAX_FD];
	char		*ptr;
	int			ret;

	if (!line || fd > MAX_FD || fd < 0)
		return (-1);
	if (str[fd] == NULL)
		if (!(str[fd] = ft_strnew(0)))
			return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ptr = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = ptr;
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && str[fd][0] == '\0')
		return (0);
	else
		return (rest_of_line(&str[fd], line));
}
