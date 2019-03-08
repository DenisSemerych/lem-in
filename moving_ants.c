#include "lem_in.h"

void change_ant(t_list **rooms, t_room *next)
{
    t_list *crawler;
    t_room *compare;

    crawler = *rooms;
    while (crawler)
    {
        compare = crawler->content;
        if (!ft_strcmp(compare->name, next->name))
        {
            compare->ant = 1;
            ft_printf("here");
        }
        crawler = crawler->next;
    }
}

int  all_at_end(t_list *ants)
{
    t_ant *ant;

    while (ants)
    {
        ant = ants->content;
        if (!ant->end)
            return (0);
        ants = ants->next;
    }
    return (1);
}


void make_move(t_ant **ant, t_list **rooms)
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

void print_path(t_list *path)
{
    t_room *room;
    while (path)
    {
        room = path->content;
        ft_printf("%s ", room->name);
        path = path->next;
    }
    ft_printf("\n");
}

t_list *give_path(t_list *paths)
{
    t_list *min;

    min = NULL;
    while (paths)
    {
        if (!min || list_count(paths->content) < list_count(min))
            min = paths->content;
        paths = paths->next;
    }
    return (min);
}

void    give_paths(t_list **ants, t_list *paths)
{
    t_list *tmp;
    t_list *crawler;
    t_list *suitable_path;
    t_ant *ant;

    tmp = paths;
    crawler = *ants;
    while (crawler)
    {
        ant = crawler->content;
        suitable_path = give_path(tmp);
        ant->path = suitable_path;
        tmp = tmp->next;
        crawler = crawler->next;
        if (!tmp)
            tmp = paths;
    }
}

void    move(t_list **rooms, t_list *ants, t_list *paths)
{
    t_ant *ant;
    t_list *tmp;

    give_paths(&ants, paths);
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
    }
}
