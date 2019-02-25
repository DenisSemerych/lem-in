#include "lem_in.h"

void algorythm(t_list **rooms)
{
    t_list *paths;
    t_list *tmp_paths;

    paths = NULL;
    while ((tmp_path = bfs(rooms, paths)))
    {
        if (count_efficiency(paths) > count_efficiency(tmp_paths))
            paths = tmp_paths;
        
    }
}


void    add_to_queue(t_list **queue, t_list *links, t_room *node)
{
    t_list *each;
    t_room *room;

    while(links)
    {
        each = ft_lstnew(NULL,0);
        each->content = links->content;
        room = each->content;
        room->from = node;
        ft_printf("from %s \n to room  %s\n ", node->name, room->name);
        *queue = add_to_the_end_of_list(*queue, each);
        links = links->next;
    }
}

void    save_path(t_room *node, t_list **paths)
{
    t_list *new;
    t_list *path;
    t_list *to_save;

    while (node->from)
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


t_list *give_start_room(t_list **rooms)
{
    t_list *crawler;
    t_room *room;

    crawler = *rooms;
    while(crawler)
    {
        room = (t_room *)crawler->content;
        if (room->is_start)
            return (crawler);
        crawler = crawler->next;
    }
    return (NULL);
}


t_list  *bfs(t_list **rooms, t_list *paths)
{
    t_list *queue;
    t_room *node;
    t_list *links;

    queue = give_start_room(rooms);
    queue->next = NULL;
    while(queue)
    {
        node = (t_room *)queue->content;
        queue = queue->next;
        links = node->links;
        if (!node->is_start && !node->is_end)
            node->is_visited = 1;
        if (node->is_end)
            save_path(node, &paths);
        else
            add_to_queue(&queue, links, node);
    }
    return (paths);
}

t_list *search_paths(t_list **rooms)
{
    t_list *paths;
    t_list *link;
    t_room *room;

    paths = bfs(rooms);
    int number = 1;
    while (paths)
    {
        ft_printf("%d path\n", number++);
        link = paths->content;
        while(link)
        {
            room = link->content;
            ft_printf("%s ", room->name);
            link = link->next;
        }
        ft_printf("\n");
        paths = paths->next;
    }
    return (NULL);
}

