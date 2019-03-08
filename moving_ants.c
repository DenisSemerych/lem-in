#include "lem_in.h"

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

void    move(t_list **rooms, t_list *ants, t_list *paths, int num_of_ants)
{
    t_ant *ant;
    give_paths(&ants, paths);
    while(ants)
    {
        ant = ants->content;
        print_path(ant->path);
        ants = ants->next;
    }
}
