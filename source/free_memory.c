/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlindhol <mlindhol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 09:21:32 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/31 12:15:12 by mlindhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Frees memory allocated to t_output *op linked list.
*/

void			lst_free(t_output *op)
{
	t_output	*current;
	t_output	*tmp;

	current = op;
	while (current->next)
	{
		tmp = current;
		current = current->next;
		free(tmp->line);
		free(tmp);
	}
	free(current->line);
	free(current);
}

/*
**	Free memory allocated to 2D array.
*/

void			free_2d_array(char **arr)
{
	int			i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
