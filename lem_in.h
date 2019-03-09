#ifndef LEM_IN_H
#define LEM_IN_H
#include "printf.h"
#include "libft.h"
#define COMPARE(a,b,c) (count_ef(a, c) > count_ef(b, c))
typedef struct s_room
{
    char *name;
    int  is_start;
    int  is_end;
    struct s_room *from;
    t_list *links;
    int  x;
    int  y;
    int  is_visited;
    int  is_closed;
    int  ant;
}              t_room;
typedef struct s_link
{
    t_room *r1;
    t_room *r2;
}               t_link;
typedef struct s_ant
{
    int   ant;
    int   end;
    t_list *path;
}              t_ant;
t_list *add_to_the_end_of_list(t_list *head, t_list *new);
void    validate(t_list *map);
void    print_list(t_list *rooms, t_list *links, t_list *ants);
t_list *create_ants(int num_of_ants, t_list *start_room);
t_link *create_link(t_room *room_one, t_room *room_two);
t_room *create_room(char *name, int x, int y, int start_end);
void    add_rooms_and_links(t_list *map, t_list **rooms);
t_list *validate_room(char *str, t_list *head, int start_end);
void    validate_link(char *str, t_list **rooms);
void    create_matrix(t_list *rooms, t_list *links, t_list *ants);
int     list_count(t_list *list);
t_list  *go_trough_rooms(t_list *rooms, int ***matrix_addr, int size);
t_list  *search_paths(t_list **rooms);
t_room *hash_function(t_list *hash_table, int index);
t_list *last_elem(t_list *head);
t_room *reverse_hash_function(int index, t_list *hash_table);
void    del_last(t_list **head);
t_list *algorythm(t_list **rooms);
t_list  *bfs(t_list **rooms);
void   add_to_queue(t_list **queue, t_room *node, t_list **paths);
void clear_rooms(t_list **rooms, t_list *path);
void    move(t_list **rooms, t_list *ants, t_list *paths);
int print_paths(t_list *tmp_paths);
void    clean(t_list **rooms, t_list **ants, t_list **paths);
#endif
