#include "lem_in.h"

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


t_list  *bfs(t_list **rooms)
{
    t_list *queue;
    t_room *node;
    t_list *links;
    t_list *paths;

    queue = ft_lstnew(NULL, 0);
    queue = give_start_room(rooms);
    paths = NULL;
    while(queue)
    {
        node = (t_room *)last_elem(queue)->content;
        del_last(&queue);
        links = node->links;
        if (node->is_end)
            save_path(node, &paths);
        else
            while (links)
            {
                queue = add_to_the_end_of_list(queue, links);
                links = links->next;
            }
    }
    return (paths);
}

t_list *search_paths(t_list **rooms)
{
    t_list *paths;

    paths = bfs(rooms);

}

