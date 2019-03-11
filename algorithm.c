/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:05:34 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/10 16:02:17 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

double count_ef(t_list *paths, int num_of_ants)
{
    int lenght;
    int num_of_paths;

    num_of_paths = list_count(paths);
    lenght = 0;
    if (!paths)
        return (42424242);
    while(paths)
    {
        lenght += list_count((t_list *)paths->content);
        paths = paths->next;
    }
    return (num_of_ants / (lenght / num_of_paths));
}

void		find_and_close(t_list *paths)
{
	t_list *crawler;
	t_room *max;
	int max_count;
	t_room *room;
	int count;

	max = NULL;
	max_count = 0;
	while (paths)
	{
		crawler = paths->content;
		while (crawler)
		{
			room = crawler->content;
			if ((count = list_count(room->links)) > max_count && !room->is_start && !room->is_end)
			{
				max_count = count;
				max = room;
			}
			crawler = crawler->next;
		}
		paths = paths->next;
	}
	if (max)
		max->is_closed = 1;
}

t_list		*algorithm(t_list **rooms, int num_of_ants)
{
	t_list	*path;
	t_list	*tmp_paths;
	t_list	*solution_with_closed;
	t_list	*solution_without_closed;

	solution_without_closed = NULL;
	while ((path = bfs(rooms)))
	{
		tmp_paths = path;
		solution_without_closed = add_to_the_end_of_list(solution_without_closed, tmp_paths);
		clear_rooms(rooms, solution_without_closed);
	}
	solution_with_closed = NULL;
	clear_rooms(rooms, NULL);
	find_and_close(solution_without_closed);
	while ((path = bfs(rooms)))
	{
		tmp_paths = path;
		solution_with_closed = add_to_the_end_of_list(solution_with_closed, tmp_paths);
		clear_rooms(rooms, solution_with_closed);
	}
	return (solution_with_closed);
}

t_list		*give_start_room(t_list **rooms)
{
	t_list	*crawler;
	t_room	*room;
	t_list	*new;

	crawler = *rooms;
	while (crawler)
	{
		room = (t_room *)crawler->content;
		if (room->is_start)
		{
			new = ft_lstnew(NULL, 0);
			new->content = crawler->content;
			return (new);
		}
		crawler = crawler->next;
	}
	return (NULL);
}

int			contains(t_list *path, t_room *node)
{
	t_room	*room;
	t_list	*crawler;

	while (path)
	{
		crawler = path->content;
		while (crawler)
		{
			room = crawler->content;
			if (room == node)
				return (1);
			crawler = crawler->next;
		}
		path = path->next;
	}
	return (0);
}

void		clear_rooms(t_list **rooms, t_list *path)
{
	t_list	*crawler;
	t_room	*room;

	crawler = *rooms;
	while (crawler)
	{
		room = crawler->content;
		if (!room->is_start && !room->is_end && contains(path, room))
			room->is_closed = 1;
		else
			room->is_closed = 0;
		room->is_visited = 0;
		crawler = crawler->next;
	}
}

t_list		*bfs(t_list **rooms)
{
	t_list	*queue;
	t_room	*node;
	t_list	*new_paths;
	t_list	*to_free;

	queue = give_start_room(rooms);
	new_paths = NULL;
	while (queue)
	{
		node = (t_room *)queue->content;
		to_free = queue;
		queue = queue->next;
		free(to_free);
		add_to_queue(&queue, node, &new_paths);
		if (new_paths)
		{
			free_queue(&queue);
			break ;
		}
	}
	return (new_paths);
}
