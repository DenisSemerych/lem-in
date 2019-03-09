/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:18:59 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/09 21:29:58 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		make_move(t_ant **ant, t_list **rooms)
{
	t_list *path;
	t_room *next;
	t_room *now;

	path = (*ant)->path;
	if ((*ant)->end)
		return ;
	now = path->content;
	next = path->next->content;
	if (next->is_end)
		(*ant)->end = 1;
	if (!next->ant)
	{
		ft_printf("L%d-%s ", (*ant)->ant, next->name);
		(*ant)->path = (*ant)->path->next;
		if (!next->is_end)
			next->ant = 1;
		now->ant = 0;
	}
}

t_list		*give_path(t_list *paths, int sum, int on_start, int prev)
{
	t_list	*min;

	min = NULL;
	if (((list_count(paths) - 1) * prev) - sum < on_start)
		min = paths;
	return (min);
}

int			all_with_paths(t_list **ants)
{
	t_list	*crawler;
	t_ant	*ant;

	crawler = *ants;
	while (crawler)
	{
		ant = crawler->content;
		if (!ant->path)
			return (0);
		crawler = crawler->next;
	}
	return (1);
}

void		give_paths(t_list **ants, t_list *paths, int on_start)
{
	t_list	*tmp;
	t_list	*crawler;
	t_ant	*ant;
	int		sum;
	int		prev;

	tmp = NULL;
	crawler = NULL;
	while (!all_with_paths(ants))
	{
		if (!tmp)
			refresh(&tmp, &sum, &prev, &paths);
		if (!crawler)
			crawler = *ants;
		ant = crawler->content;
		sum += list_count(tmp->content);
		prev++;
		ant->path = give_path(tmp->content, sum, on_start, prev);
		if (ant->path)
		{
			on_start--;
			crawler = crawler->next;
		}
		tmp = tmp->next;
	}
}

void		move(t_list **rooms, t_list *ants, t_list *paths, int num_of_ants)
{
	t_ant	*ant;
	t_list	*tmp;
	int		count;

	give_paths(&ants, paths, num_of_ants);
	count = 0;
	while (!all_at_end(ants))
	{
		tmp = ants;
		while (tmp)
		{
			ant = tmp->content;
			make_move(&ant, rooms);
			tmp = tmp->next;
		}
		ft_printf("\n");
		count++;
	}
	ft_printf("%d number of lines", count);
}
