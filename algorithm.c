#include "lem_in.h"

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

void print_rooms(t_list **rooms)
{
    t_list *crawler = *rooms;

    while (crawler)
    {
        t_room *room = crawler->content;
        ft_printf("%s %d %d\n", room->name, room->is_closed, room->is_visited);
        crawler = crawler->next;
    }
}


//t_list *contains(t_list **paths, t_room *node)
//{
//    t_list *crawler;
//    t_list *path;
//    t_room *room;
//
//    crawler = *paths;
//
//    while (crawler)
//    {
//        path = crawler->content;
//        while (path)
//        {
//            room = path->content;
//            if (room == node)
//                return (path);
//            path = path->next;
//        }
//        crawler = crawler->next;
//    }
//    return (NULL);
//}

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

//void delete_path(t_list **paths, t_list *path)
//{
//    t_list *crawler;
//    t_list *prev;
//
//    crawler = *paths;
//    prev = NULL;
//    while (crawler)
//    {
//        if (crawler->content == path)
//        {
//            prev->next = crawler->next;
//            break ;
//        }
//        prev = crawler;
//        crawler = crawler->next;
//    }
//}

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
            else if (!room->is_closed && (check = 1))
               // ft_printf("add to queue %s\n", room->name);
                *queue = add_to_the_end_of_list(*queue, each);
        }
        links = links->next;
    }
    return (check);
}



int print_paths(t_list *tmp_paths)
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
    return (0);
}

t_list *algorythm(t_list **rooms, int num_of_ants)
{
    t_list *paths;
    t_list *tmp_paths;
    t_list *optim;

    paths = bfs(rooms);
    optim = NULL;
    while (paths)
    {
        tmp_paths = ft_lstnew(NULL, 0);
        tmp_paths->content = paths->content;
        clear_rooms(rooms, paths);
        tmp_paths = add_to_the_end_of_list(tmp_paths, bfs(rooms));
        if (COMPARE(optim, tmp_paths, num_of_ants))
            optim = tmp_paths;
        paths = paths->next;
    }
    print_paths(optim);
    return (optim);
}

t_list *give_start_room(t_list **rooms)
{
    t_list *crawler;
    t_room *room;
    t_list *new;

    crawler = *rooms;
    while (crawler)
    {
        room = (t_room *) crawler->content;
        if (room->is_start) {
            new = ft_lstnew(NULL, 0);
            new->content = crawler->content;
            return (new);
        }
        crawler = crawler->next;
    }
    return (NULL);
}



int contains_int(t_list *path, t_room *node)
{
    t_room *room;


    path = path->content;
    while (path)
    {
        room = path->content;
        if (room == node)
            return (1);
        path = path->next;
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
        if (!room->is_start && !room->is_end && contains_int(path, room))
            room->is_closed = 1;
        else
            room->is_closed = 0;
        room->is_visited = 0;
        crawler = crawler->next;
    }
}

t_list  *bfs(t_list **rooms)
{
    t_list *queue;
    t_room *node;
    t_list *new_paths;

    queue = give_start_room(rooms);
    new_paths = NULL;
    while(queue)
    {
        node = (t_room *)queue->content;
        queue = queue->next;
        add_to_queue(&queue, node, &new_paths);
    }
    return (new_paths);
}
//
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

