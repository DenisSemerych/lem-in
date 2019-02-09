#include "lem_in.h"

t_list *bfs(int ***matrix_addr, t_list *hash_table, int size)
{
    t_list *queue;
    int    **matrix;
    t_room *node;
    int    child;
    int    index;

    matrix = *matrix_addr;
    queue = ft_lstnew(NULL, 0);
    queue->content = hash_function(hash_table, 0);
    while(queue)
    {
        node = (t_room *)last_elem(queue)->content;
        if (node->is_end)
            return (queue);
        while(index < size)
        {
            child = hash_function(hash_table, NULL, node)
        }
    }
}

t_list *search_paths(int **matrix, int number_of_ants, t_list *hash_table, int size)
{
    t_list *paths;
    t_list *path;

    paths = NULL;
    while(number_of_ants)
    {
        path = bfs(&matrix, hash_table);
        paths = add_to_the_end_of_list(paths, path, size);
        number_of_ants--;
    }
}

