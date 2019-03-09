/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:30:54 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/09 20:48:27 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	new = ft_lstnew(NULL, 0);
	new->content = room;
	head = add_to_the_end_of_list(head, new);
	free_str_arr(info, 3);
	return (head);
}

void		set_links(t_room **room_one, t_room **room_two)
{
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
		put_err_msg_exit("Error: one of the links is invalid");
	set_links(&room_one, &room_two);
	free_str_arr(info, 2);
}

t_list		*check_rooms(t_list *rooms)
{
	t_room	*room;
	int		check_start;
	int		check_end;
	int		count;
	t_list	*start;

	check_start = 0;
	check_end = 0;
	count = 0;
	while (rooms)
	{
		room = (t_room *)rooms->content;
		if (room->is_end)
			check_end += 1;
		if (room->is_start)
		{
			check_start += 1;
			start = rooms;
		}
		rooms = rooms->next;
		count++;
	}
	if (check_end != 1 || check_start != 1 || count < 2)
		put_err_msg_exit(ERROR_ROOMS);
	return (start);
}

void		validate(t_list *map)
{
	int		num_of_ants;
	t_list	*ants;
	t_list	*rooms;
	t_list	*paths;
	t_list	*to_print;

	to_print = map;
	if ((num_of_ants = ft_atoi(map->content)) <= 0)
		put_err_msg_exit("Error: incorrect number of ants");
	map = map->next;
	rooms = NULL;
	add_rooms_and_links(map, &rooms);
	ants = create_ants(num_of_ants, check_rooms(rooms));
	paths = algorythm(&rooms);
	print_map(to_print);
	move(&rooms, ants, paths, num_of_ants);
	clean(&rooms, &ants, &paths);
}
