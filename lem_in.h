/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemeryc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:08:45 by dsemeryc          #+#    #+#             */
/*   Updated: 2019/03/09 21:15:41 by dsemeryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "printf.h"
# include "libft.h"
# define ERROR_ROOMS "Error: invalid map(more than one start/end ect)"

typedef struct		s_room
{
	char			*name;
	int				is_start;
	int				is_end;
	struct s_room	*from;
	t_list			*links;
	int				x;
	int				y;
	int				is_visited;
	int				is_closed;
	int				ant;
}					t_room;
typedef struct		s_link
{
	t_room			*r1;
	t_room			*r2;
}					t_link;
typedef struct		s_ant
{
	int				ant;
	int				end;
	t_list			*path;
}					t_ant;

t_list				*add_to_the_end_of_list(t_list *head, t_list *new);
void				validate(t_list *map);
void				free_queue(t_list **queue);
t_list				*create_ants(int num_of_ants, t_list *start_room);
t_room				*create_room(char *name, int x, int y, int start_end);
void				add_rooms_and_links(t_list *map, t_list **rooms);
t_list				*validate_room(char *str, t_list *head, int start_end);
void				validate_link(char *str, t_list **rooms);
int					list_count(t_list *list);
t_list				*last_elem(t_list *head);
t_list				*algorythm(t_list **rooms);
t_list				*bfs(t_list **rooms);
void				add_to_queue(t_list **queue, t_room *node, t_list **paths);
void				clear_rooms(t_list **rooms, t_list *path);
void				move(t_list **rooms, t_list *ants, t_list *paths, int num_of_ants);
int					print_paths(t_list *tmp_paths);
void				clean(t_list **rooms, t_list **ants, t_list **paths);
void				print_map(t_list *map);
void				refresh(t_list **tmp, int *sum, int *prev, t_list **paths);
int					all_at_end(t_list *ants);
#endif
