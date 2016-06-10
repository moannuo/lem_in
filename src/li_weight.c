/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_weight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 14:05:42 by ademenet          #+#    #+#             */
/*   Updated: 2016/06/10 13:38:30 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
** Here we assign weight.
*/

int					li_weight_recursive(t_graph *data, t_room *cur, int weight)
{
	// static int		depth = 0;
	int				i;

	DBfct
	if (cur == data->start)
		return (0);
	i = 0;
	while (cur->tube[i] != NULL)
	{
		if (cur->tube[i]->weight == -1 && cur->tube != NULL)
		{
			cur->tube[i]->weight = weight;
			cur = cur->tube[i];
			li_weight_recursive(data, cur, (weight + 1));
		}
		i++;
	}
	return (1);
}

int					li_weight(t_graph *data)
{
	int				weight;
	t_room			*cur;

	cur = data->end;
	cur->weight = 0;
	weight = 1;
	li_weight_recursive(data, cur, weight);

	t_room	*tmp;
	tmp = data->head;
	while (tmp)
	{
		printf("weight de %s : [%d]\n", tmp->name, tmp->weight);
		tmp = tmp->next;
	}

	return (1);
}