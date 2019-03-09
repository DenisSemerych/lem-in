//#include "lem_in.h"
//
//t_room *hash_function(t_list *hash_table, int index)
//{
//    while(hash_table)
//    {
//        if (index == hash_table->content_size)
//            return ((t_room *)hash_table->content);
//        hash_table = hash_table->next;
//    }
//    put_err_msg_exit("Error: something went wrong while working with hash-function");
//    return (NULL);
//}
//
//int     check_link(t_room *room, int index, t_list *hash_table, t_list *links)
//{
//    t_link *link;
//    t_room *matching_room;
//
//    matching_room = hash_function(hash_table, index);
//    while(links)
//    {
//        link = (t_link *)links->content;
//        if ((matching_room == link->r1 && room == link->r2) || (matching_room == link->r2 && room == link->r1))
//            return (1);
//        links = links->next;
//    }
//    return (0);
//}
//
//void    fill_rows(int size, int ***matrix_addr, t_list *links, t_list *hash_table)
//{
//    int **matrix;
//    int count_r;
//    int count_c;
//    t_room *room;
//    t_list *tmp;
//
//    matrix = *matrix_addr;
//    count_r = 0;
//    while (count_r < size)
//    {
//        count_c = 0;
//        room = hash_function(hash_table, count_r);
//        while (count_c < size)
//        {
//            matrix[count_r][count_c] = count_c <= count_r ? 0 : check_link(room, count_c, hash_table, links);
//            count_c++;
//        }
//        count_r++;
//    }
//}
//
//t_list   *go_trough_rooms(t_list *rooms, int ***matrix_addr, int size)
//{
//    t_room *room;
//    int index;
//    t_list *hash_table;
//    int **matrix;
//    int added;
//
//    index = 1;
//    matrix = *matrix_addr;
//    hash_table = NULL;
//    while(rooms)
//    {
//        room = (t_room *)rooms->content;
//        if (room->is_start && !(added = 0))
//            matrix[0] = (int *)malloc(sizeof(int) * size);
//        else if (room->is_end && (added = size - 1))
//            matrix[size - 1] = (int *)malloc(sizeof(int) * size);
//        else
//        {
//            added = index;
//            matrix[index++] = (int *)malloc(sizeof(int) * size);
//        }
//        ft_lstadd(&hash_table, ft_lstnew(NULL, 0));
//        hash_table->content = room;
//        hash_table->content_size = added;
//        rooms = rooms->next;
//    }
//    return (hash_table);
//}
//
//void    create_matrix(t_list *rooms, t_list *links, t_list *ants)
//{
//    int **matrix;
//    t_list *hash_table;
//    t_room *room;
//    int size;
//    t_list *paths;
//
//    size = list_count(rooms);
//    matrix = (int **) malloc((sizeof(int) * size) * size);
//    hash_table = go_trough_rooms(rooms, &matrix, size);
//    fill_rows(size, &matrix, links, hash_table);
//    int i = 0;
//    while (i < size)
//    {
//        int j = 0;
//        while (j < size)
//        {
//            ft_printf("%d ", matrix[i][j]);
//            j++;
//        }
//        ft_printf("\n");
//        i++;
//    }
//    paths = search_paths(matrix, list_count(ants), hash_table, size);
//}

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

//t_list *algorythm(t_list **rooms, int num_of_ants)
//{
//    t_list *paths;
//    t_list *tmp_paths;
//    t_list *optim;
//
//    paths = bfs(rooms);
//    optim = NULL;
//    while (paths)
//    {
//        tmp_paths = ft_lstnew(NULL, 0);
//        tmp_paths->content = paths->content;
//        clear_rooms(rooms, tmp_paths);
//        tmp_paths = add_to_the_end_of_list(tmp_paths, bfs(rooms));
//        if (COMPARE(optim, tmp_paths, num_of_ants))
//            optim = tmp_paths;
//        paths = paths->next;
//    }
//    print_paths(optim);
//    return (optim);
//}
//void print_rooms(t_list **rooms)
//{
//    t_list *crawler = *rooms;
//
//    while (crawler)
//    {
//        t_room *room = crawler->content;
//        ft_printf("%s %d %d\n", room->name, room->is_closed, room->is_visited);
//        crawler = crawler->next;
//    }
//}
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

//    while (rooms)
//    {
//        t_room *room = (t_room *)rooms->content;
//        t_list *links = room->links;
//        while (links)
//        {
//            t_room *to;
//            to = links->content;
//            ft_printf("room %s connected with room %s\n", room->name, to->name);
//            links = links->next;
//        }
//        rooms = rooms->next;
//    }

//
//void    print_list(t_list *rooms, t_list *links, t_list *ants)
//{
//
//    while (rooms)
//    {
//        t_room *room = (t_room *)rooms->content;
//        ft_printf("%s\n x:%d y:%d\n", room->name, room->x, room->y);
//        rooms = rooms->next;
//    }
//    while (links)
//    {
//        t_link *link = (t_link *)links->content;
//        t_room *room1 = link->r1;
//        t_room *room2 = link->r2;
//        printf("%s room one linked with %s room two\n", room1->name, room2->name);
//        links = links->next;
//    }
//    while (ants)
//    {
//
//        t_ant *ant = (t_ant *)ants->content;
//        t_room *ant_room = (t_room *)ant->room->content;
//        printf("L%d at the %s room\n", ant->ant, ant_room->name);
//        ants = ants->next;
//    }
//}