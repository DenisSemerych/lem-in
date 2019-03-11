/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:13:36 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/10 16:03:53 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void 		parsing_map_info(char *map_content, unsigned char *commands_num, t_list **rooms, int *start_end)
{
	if (!ft_strcmp(map_content, "##start") && !(*commands_num & 0b10000000) && (*commands_num = *commands_num | 0b10000000))
		*start_end = 1;
	else if (!ft_strcmp(map_content, "##start"))
		put_err_msg_exit("You can pass start command only once");
	else if (!ft_strcmp(map_content, "##end") && !(*commands_num & 0b00000000) && (*commands_num = *commands_num | 0b00000001))
		*start_end = 2;
	else if (!ft_strcmp(map_content, "##end"))
		put_err_msg_exit("You can pass end command only once");
	else if (!ft_strncmp(map_content, "##", 2))
		;
	else if (ft_strchr(map_content, '-') && !rooms)
		put_err_msg_exit("Error: you add a link before adding a room");
	else if (ft_strchr(map_content, '-') && rooms)
		validate_link(map_content, rooms);
	else if (!ft_strncmp(map_content, "#", 1))
		;
	else
	{
		*rooms = validate_room(map_content, *rooms, *start_end);
		*start_end ? (*start_end = 0) : *start_end;
	}
}

void		add_rooms_and_links(t_list *map, t_list **rooms)
{
	int		start_end;
	unsigned char commands_num;

	start_end = 0;
	commands_num = 0b00000000;
	while (map)
	{
		parsing_map_info(map->content, &commands_num, rooms, &start_end);
		map = map->next;
	}
	if (!(commands_num & 0b10000000))
		put_err_msg_exit("##start is missing");
	else if (!(commands_num & 0b00000001))
		put_err_msg_exit("##end is missing");
}

t_list		*create_ants(int num_of_ants)
{
	t_list	*head;
	t_ant	*ant;
	t_list	*new;

	head = NULL;
	while (num_of_ants)
	{
		ant = (t_ant *)malloc(sizeof(t_ant));
		ant->ant = num_of_ants;
		ant->path = NULL;
		ant->end = 0;
		new = ft_lstnew(NULL, 0);
		new->content = ant;
		ft_lstadd(&head, new);
		num_of_ants--;
	}
	return (head);
}

t_room		*create_room(char *name, int x, int y, int start_end)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	room->x = x;
	room->y = y;
	room->name = ft_strdup(name);
	room->is_start = (start_end == 1 ? 1 : 0);
	room->is_end = (start_end == 2 ? 1 : 0);
	room->from = NULL;
	room->is_visited = 0;
	room->is_closed = 0;
	room->ant = 0;
	return (room);
}
