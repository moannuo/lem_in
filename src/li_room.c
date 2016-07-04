/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 11:22:41 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/04 17:35:37 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/*
** Start or end commands handler. If we recognize one command I point it with
** the right value. If not, that is to say the start or end is allready
** allocated, we return an error.
*/

int					li_room_start_end(t_graph *data, int *com)
{
	if (*com == 1 && data->start == NULL)
		data->start = data->head;
	else if (*com == 2 && data->end == NULL)
		data->end = data->head;
	else if (*com == 1 && data->start != NULL)
		return (-7);
	else if (*com == 2 && data->start != NULL)
		return (-7);
	if (*com != 0)
		*com = 0;
	return (1);
}

/*
** Add a new room to the list beginning. Check also if its room is start or end.
*/

int					li_room_add(t_graph *data, char *name, int *com)
{
	t_room			*new;

	if (data->head == NULL)
	{
		new = (t_room*)malloc(sizeof(t_room));
		new->name = name;
		new->weight = -1;
		new->tube = NULL;
		new->next = NULL;
		new->prev = NULL;
		data->head = new;
	}
	else
	{
		new = (t_room*)malloc(sizeof(t_room));
		new->name = name;
		new->weight = -1;
		new->tube = NULL;
		data->head->prev = new;
		new->prev = NULL;
		new->next = data->head;
		data->head = new;
	}
	return (li_room_start_end(data, com));
}

/*
** Just check if coordinates are goods: it should be a positive integer only.
*/

int					li_room_check_coord(char *line)
{
	int				i;
	long			nb;

	i = 0;
	nb = 0;
	if (line[0] == '-')
		return (-1);
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]))
			i++;
		else
			return (-1);
	}
	nb = ft_atoi(line);
	if (nb > INT_MAX)
		return (-1);
	return (1);
}

void				li_clean_split_line(char *first, char *second, char **tab)
{
	free(first);
	free(second);
	free(tab);
}

/*
** The rooms are defined as it: name coord_x coord_y.
*/

int					li_room_get(char *line, t_graph *data, int *com)
{
	char			**split_line;
	int				len;

	split_line = ft_strsplit(line, ' ');
	len = li_array_len((void**)split_line);
	if (len == 1)
	{
		free(split_line[0]);
		free(split_line);
		return (li_tube_get(line, data));
	}
	if (len != 3)
		return (-4);
	len = -1;
	while (split_line[0][++len] != '\0')
	{
		if (split_line[0][len] == '-' || split_line[0][0] == 'L')
			return (-5);
	}
	if (li_room_check_coord(split_line[1]) == -1 ||
		li_room_check_coord(split_line[2]) == -1)
		return (-6);
	li_clean_split_line(split_line[1], split_line[2], split_line);
	return (li_room_add(data, split_line[0], com));
}
