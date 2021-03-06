/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_tube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:40:25 by ademenet          #+#    #+#             */
/*   Updated: 2016/06/27 16:53:32 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
** If we allready had some rooms in our tube array, copy it and add the new
** one.
*/

t_room				**li_tube_copy(t_room **tube, t_room *to_link)
{
	t_room			**new_tube;
	int				i;
	int				len;

	i = -1;
	len = -1;
	while (tube[++len] != NULL)
		;
	new_tube = (t_room**)malloc(sizeof(t_room*) * (len + 2));
	while (tube[++i] != NULL)
		new_tube[i] = tube[i];
	new_tube[len] = to_link;
	new_tube[len + 1] = NULL;
	free(tube);
	return (new_tube);
}

/*
** Linking rooms: add room2 in room1 tube array.
*/

void				li_tube_dig(t_room *room1, t_room *room2)
{
	if (room1->tube == NULL)
	{
		room1->tube = (t_room**)malloc(sizeof(t_room*) * 2);
		room1->tube[0] = room2;
		room1->tube[1] = NULL;
	}
	else if (room1->tube != NULL)
		room1->tube = li_tube_copy(room1->tube, room2);
}

/*
** Find the node corresponding to the name and return its adress.
*/

t_room				*li_tube_room_find(char *name, t_graph *data)
{
	t_room			*tmp;

	tmp = data->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** Rooms are linked with tubes, tubes are given as follows: name1-name2.
*/

int					li_tube_get(char *line, t_graph *data)
{
	char			**split_line;
	t_room			*room1;
	t_room			*room2;
	int				len;

	split_line = ft_strsplit(line, '-');
	len = -1;
	while (split_line[++len])
		;
	if (len != 2)
		return (-1);
	room1 = li_tube_room_find(split_line[0], data);
	room2 = li_tube_room_find(split_line[1], data);
	if (room1 == NULL || room2 == NULL)
		return (-1);
	li_tube_dig(room1, room2);
	li_tube_dig(room2, room1);
	free(split_line[0]);
	free(split_line[1]);
	free(split_line);
	return (2);
}
