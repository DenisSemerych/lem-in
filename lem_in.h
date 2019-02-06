#ifndef LEM_IN_H
#define LEM_IN_H
#include "printf.h"
#include "libft.h"
typedef struct s_room
{
    char *name;
    int  is_start;
    int  is_end;
    int  x;
    int  y;
}              t_room;
typedef struct s_link
{
    char *r1;
    char *r2;
}               t_link;
typedef struct s_ant
{
    int   ant;
    t_list *room;
}              t_ant;
t_list *add_to_the_end_of_list(t_list *head, t_list *new);
void    validate(t_list *map);
void    print_list(t_list *rooms, t_list *links, t_list *ants);
t_list *create_ants(int num_of_ants, t_list *start_room);
t_link *create_link(char *name_one, char *name_two);
t_room *create_room(char *name, int x, int y, int start_end);
void    add_rooms_and_links(t_list *map, t_list **links, t_list **rooms);
t_list *validate_room(char *str, t_list *head, int start_end);
t_list *validate_link(char *str, t_list *head, t_list *rooms);
#endif
