//#include "lem_in.h"
//
//void    add_to_queue(int index, t_list **queue, t_list *hash_table)
//{
//    t_room *room;
//    t_list *new;
//
//    room = reverse_hash_function(index, hash_table);
//    new = ft_lstnew(NULL, 0);
//    new->content = room;
//    new->content_size = index;
//    *queue = add_to_the_end_of_list(*queue, new);
//}
//
//void    add_to_path(int room_one, int room_two, t_list **path, t_list *hash_table)
//{
//    t_room *first_room;
//    t_room *second_room;
//    t_link *link;
//
//    first_room = reverse_hash_function(room_one, hash_table);
//    second_room = reverse_hash_function(room_two, hash_table);
//    ft_printf("%s first %s second\n", first_room->name, second_room->name);
//    link = (t_link *)malloc(sizeof(t_link));
//    link->r1 = first_room;
//    link->r2 = second_room;
//    *path = add_to_the_end_of_list(*path, ft_lstnew(link, sizeof(t_link)));
//}
//
//
//t_list *bfs(int ***matrix_addr, t_list *hash_table, int size)
//{
//    t_list *queue;
//    int    **matrix;
//    t_room *node;
//    t_list *solution;
//    t_list *path;
//    int index;
//    int node_index;
//    t_list *new_path;
//
//    matrix = *matrix_addr;
//    queue = ft_lstnew(NULL, 0);
//    queue->content = hash_function(hash_table, 0);
//    solution = NULL;
//    path = NULL;
//    while(queue)
//    {
//        index = 0;
//        node = (t_room *)last_elem(queue)->content;
//        node_index = last_elem(queue)->content_size;
//        del_last(&queue);
//        if (node->is_end){
//            new_path = ft_lstnew(NULL, 0);
//            new_path->content = path;
//            solution = add_to_the_end_of_list(solution, new_path);
//        }
//        while(index < size)
//            if (matrix[node_index][index++] == 1)
//            {
//                add_to_path(node_index, index - 1,&path, hash_table);
//                add_to_queue(index - 1, &queue, hash_table);
//            }
//    }
//    return (solution);
//}
//
//t_list *search_paths(int **matrix, int number_of_ants, t_list *hash_table, int size)
//{
//    t_list *paths;
//
//    paths = NULL;
//    paths = bfs(&matrix, hash_table, size);
//    while (paths)
//    {
//        t_list *path = paths->content;
//        while(path)
//        {
//            t_link *link = path->content;
//            t_room *room_one = link->r1;
//            t_room *room_two = link->r2;
//            ft_printf("from %s  to %s\n", room_one->name, room_two->name);
//            path = path->next;
//        }
//        paths = paths->next;
//    }
//    return (paths);
//}

