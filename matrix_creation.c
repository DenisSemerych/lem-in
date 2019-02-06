#include <strhash.h>
#include "lem_in.h"

t_room *hash_function(t_list *hash_table, int index)
{
    while(hash_table)
    {
        if (index == hash_table->content_size)
            return ((t_room *)hash_table->content);
        hash_table = hash_table->next;
    }
    put_err_msg_exit("Error: something went wrong while working with hash-function");
}

void    fill_rows(int size, int ***matrix_addr, t_list *links, t_list *hash_table)
{
    int **matrix;
    int count_r;
    int count_c;
    t_room *room;
    t_list *tmp;

    matrix = *matrix_addr;
    count_r = 0;
    while (count_r < size)
    {
        count_c = 0;
        room = hash_function(hash_table, count_r);
        while (count_c < size)
        {
            
        }
        count_r++;
    }
}

t_list   *go_trough_rooms(t_list *rooms, int ***matrix_addr, int size)
{
    t_room *room;
    int index;
    t_list *hash_table;
    int **matrix;
    int added;

    index = 1;
    matrix = *matrix_addr;
    hash_table = NULL;
    while(rooms)
    {
        room = (t_room *)rooms->content;
        if (room->is_start && !(added = 0))
            matrix[0] = (int *)malloc(size);
        else if (room->is_end && (added = size - 1))
            matrix[size - 1] = (int *)malloc(size);
        else if ((added = index))
            matrix[index++] = (int *)malloc(size);
        ft_lstadd(&hash_table, ft_lstnew(NULL, 0));
        hash_table->content = rooms;
        hash_table->content_size = added;
        rooms = rooms->next;
    }
    return (hash_table);
}

void    create_matrix(t_list *rooms, t_list *links)
{
    int **matrix;
    t_list *hash_table;
    t_room *room;
    int size;

    size = list_count(rooms);
    matrix = (int **) malloc(size);
    hash_table = go_trough_rooms(rooms, &matrix, size);
    int i = 0;
    fill_rows(size, &matrix, links, hash_table);
    while (i < size)
    {
        int j = 0;
        while (j < size)
        {
            ft_printf("%d ", matrix[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}