#include "lem_in.h"

void   free_queue(t_list **queue)
{
    t_list *to_free;

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

void   add_to_queue(t_list **queue, t_room *node, t_list **paths)
{
    t_list *each;
    t_room *room;
    t_list *links;

    links = node->links;
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

int print_paths(t_list *tmp_paths)
{
    t_list *link;
    t_room *room;
    int number = 1;
    ft_printf("HERE IS PATHS FOR ALL ANTS\n");
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

t_list *algorythm(t_list **rooms)
{
    t_list *path;
    t_list *tmp_paths;
    t_list *solution;


    solution = NULL;
    while ((path = bfs(rooms)))
    {
        tmp_paths = path;
        print_paths(tmp_paths);
        solution = add_to_the_end_of_list(solution, tmp_paths);
        clear_rooms(rooms, solution);
    }
    return (solution);
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
    t_list *crawler;

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
    t_list *to_free;

    queue = give_start_room(rooms);
    new_paths = NULL;
    while(queue)
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
