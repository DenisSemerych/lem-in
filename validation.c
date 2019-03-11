/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:30:54 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/10 16:06:40 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void        check_rooms(t_list *rooms, t_room *to_find)
{
    t_room *room;

    while (rooms)
    {
        room = rooms->content;
        if (!ft_strcmp(room->name, to_find->name))
            put_err_msg_exit("Rooms can`t have same names");
        rooms = rooms->next;
    }
}

t_list		*validate_room(char *str, t_list *head, int start_end)
{
	char	**info;
	t_room	*room;
	t_list	*new;

	info = ft_strsplit(str, ' ');
	if (count_size(info) != 3 ||
			spec_atoi(info[1]) < 0 || spec_atoi(info[2]) < 0 ||
			info[0][0] == 'L' || info[0][0] == '#' || info[0][0] == '\0')
		put_err_msg_exit("Error: one of the rooms is invalid");
	room = create_room(info[0],
			spec_atoi(info[1]), spec_atoi(info[2]), start_end);
	check_rooms(head, room);
	new = ft_lstnew(NULL, 0);
	new->content = room;
	head = add_to_the_end_of_list(head, new);
	free_str_arr(info, 3);
	return (head);
}

void		set_links(t_room **room_one, t_room **room_two)
{
	if ((*room_one)->is_start && (*room_two)->is_end)
		put_err_msg_exit("You have link from start to end - 1 turn needed");
	(*room_one)->links =
		add_to_the_end_of_list((*room_one)->links, ft_lstnew(NULL, 0));
	last_elem((*room_one)->links)->content = *room_two;
	(*room_two)->links =
		add_to_the_end_of_list((*room_two)->links, ft_lstnew(NULL, 0));
	last_elem((*room_two)->links)->content = *room_one;
}

void		validate_link(char *str, t_list **rooms_add)
{
	char	**info;
	t_room	*room_one;
	t_room	*room_two;
	t_room	*room;
	t_list	*rooms;

	info = ft_strsplit(str, '-');
	if (count_size(info) != 2)
		put_err_msg_exit("Error: one of the links is invalid");
	room_one = NULL;
	room_two = NULL;
	rooms = *rooms_add;
	while (rooms)
	{
		room = (t_room *)(rooms->content);
		if (!ft_strcmp(room->name, info[0]))
			room_one = room;
		else if (!ft_strcmp(room->name, info[1]))
			room_two = room;
		rooms = rooms->next;
	}
	if (!room_two || !room_one)
		put_err_msg_exit("Error: some links is invalid");
	set_links(&room_one, &room_two);
	free_str_arr(info, 2);
}

void		validate(t_list *map, int params)
{
	int		num_of_ants;
	t_list	*ants;
	t_list	*rooms;
	t_list	*paths;
	t_list	*to_print;

	to_print = map;
	if ((num_of_ants = spec_atoi(map->content)) <= 0)
		put_err_msg_exit("Error: incorrect number of ants");
	map = map->next;
	rooms = NULL;
	add_rooms_and_links(map, &rooms);
	if (list_count(rooms) < 2)
		put_err_msg_exit("You can give start/end command only once");
	ants = create_ants(num_of_ants);
	paths = algorithm(&rooms, num_of_ants);
	switch_prarams(params, to_print, paths);
	num_of_ants = move(ants, paths, num_of_ants);
	if (params == 4)
		ft_printf("%s\nWas made %d moves\n%s", GRN, num_of_ants, RESET);
	clean(&rooms, &ants, &paths);
}
