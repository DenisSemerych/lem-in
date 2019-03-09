/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:59:30 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/09 21:05:57 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*last_elem(t_list *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void		save_path(t_room *node, t_list **paths)
{
	t_list	*new;
	t_list	*path;
	t_list	*to_save;

	while (node)
	{
		new = ft_lstnew(NULL, 0);
		new->content = node;
		ft_lstadd(&path, new);
		node = node->from;
	}
	to_save = ft_lstnew(NULL, 0);
	to_save->content = path;
	*paths = add_to_the_end_of_list(*paths, to_save);
}

void		free_queue(t_list **queue)
{
	t_list	*to_free;

	if (!queue)
		return ;
	while (*queue)
	{
		to_free = *queue;
		free(to_free);
		*queue = (*queue)->next;
	}
	free(*queue);
}

void		add_to_queue(t_list **queue, t_room *node, t_list **paths)
{
	t_list	*each;
	t_room	*room;
	t_list	*links;

	links = node->links;
	while (links)
	{
		each = ft_lstnew(NULL, 0);
		each->content = links->content;
		room = each->content;
		if (!(room->is_visited + room->is_start))
		{
			room->from = node;
			!room->is_end ? (room->is_visited = 1) : 0;
			if (room->is_end)
				save_path(node, paths);
			else if (!room->is_closed)
				*queue = add_to_the_end_of_list(*queue, each);
			else
				free(each);
		}
		else
			free(each);
		links = links->next;
	}
}
