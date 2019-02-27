#include "lem_in.h"

void    save_path(t_room *node, t_list **paths)
{
    t_list *new;
    t_list *path;
    t_list *to_save;

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

t_room *roll_back(t_room *node, t_list **queue, t_list **paths)
{
    node = node->from;
    node->is_visited = 0;
    while (node->from)
    {
        if (add_to_queue(queue, node, paths))
            return (node);
        node = node->from;
    }
    return (NULL);
}

int   add_to_queue(t_list **queue, t_room *node, t_list **paths)
{
    t_list *each;
    t_room *room;
    t_list *links;
    int    check;

    links = node->links;
    check = 0;
    while(links)
    {
        each = ft_lstnew(NULL,0);
        each->content = links->content;
        room = each->content;
        if (!(room->is_visited + room->is_start))
        {
            room->from = node;
            if (!room->is_end)
                room->is_visited = 1;
            if (room->is_end)
                save_path(node, paths);
            else
            {
                ft_printf("add to queue %s\n", room->name);
                if (room->is_closed)
                    roll_back(room, queue, paths);
                if (!room->is_closed)
                    *queue = add_to_the_end_of_list(*queue, each);
                check = 1;
            }
        }
        links = links->next;
    }
    return (check);
}



int efficiency(t_list *paths, t_list *tmp_paths)
{
    t_list *link;
    t_room *room;
    int number = 1;
    while (tmp_paths)
    {
        ft_printf("%d path\n", number++);
        link = tmp_paths->content;
        while(link)
        {
            room = link->content;
            ft_printf("%s ", room->name);
            link = link->next;
        }
        ft_printf("\n");
        tmp_paths = tmp_paths->next;
    }
    return (1);
}

t_list *algorythm(t_list **rooms)
{
    t_list *paths;
    t_list *tmp_paths;

    paths = NULL;
    while ((tmp_paths = bfs(rooms, paths)))
        if (efficiency(paths, tmp_paths))
            paths = tmp_paths;
    return (paths);
}

t_list *give_start_room(t_list **rooms)
{
    t_list *crawler;
    t_room *room;
    t_list *new;

    crawler = *rooms;
    while(crawler)
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

t_room *contains(t_list **paths, t_room *node, t_list **queue)
{
    t_list *crawler;
    t_list *path;
    t_room *room;

    crawler = *paths;

    while (crawler)
    {
        path = crawler->content;
        while (path)
        {
            room = path->content;
            if (room == node)
                return (roll_back(room, queue, paths));
            path = path->next;
        }
        crawler = crawler->next;
    }
    return (NULL);
}

int contains_int(t_list *path, t_room *node)
{
    t_list *crawler;
    t_room *room;

    crawler = path;
    while (crawler)
    {
        path = crawler->content;
        while (path)
        {
            room = path->content;
            if (room == node)
                return (1);
            path = path->next;
        }
        crawler = crawler->next;
    }
    return (0);
}


void clear_rooms(t_list **rooms, t_list *path)
{
    t_list *crawler;
    t_room *room;

    crawler = *rooms;
    while (crawler)
    {
        room = crawler->content;
        if (contains_int(path, room) && !room->is_start && !room->is_end)
            room->is_closed = 1;
        room->is_visited = 0;
        crawler = crawler->next;
    }
}

t_list  *bfs(t_list **rooms, t_list *paths)
{
    t_list *queue;
    t_room *node;
    t_room *from;
    t_list *new_paths;

    queue = give_start_room(rooms);
    new_paths = NULL;
    while(queue)
    {
        node = (t_room *)queue->content;
        queue = queue->next;
        if (!node->is_start && (from = contains(&paths, node, &queue)))
            add_to_queue(&queue, from, &new_paths);  
        else
            add_to_queue(&queue, node, &new_paths);
    }
    clear_rooms(rooms, new_paths);
    return (new_paths);
}

//t_list *search_paths(t_list **rooms)
//{
//    algorythm(rooms);
//
////    int number = 1;
////    while (paths)
////    {
////        ft_printf("%d path\n", number++);
////        link = paths->content;
////        while(link)
////        {
////            room = link->content;
////            ft_printf("%s ", room->name);
////            link = link->next;
////        }
////        ft_printf("\n");
////        paths = paths->next;
////    }
//    return (NULL);
//}

