#include "lem_in.h"

void    add_rooms_and_links(t_list *map, t_list **links, t_list **rooms)
{
    int start_end;

    start_end = 0;
    while(map)
    {
        if (!ft_strncmp(map->content, "##start", 7))
            start_end = 1;
        else if (!ft_strncmp(map->content, "##end", 5))
            start_end = 2;
        else if (!ft_strncmp(map->content, "##", 2))
            ;
        else if (ft_strchr(map->content, '-') && !rooms)
            put_err_msg_exit("Error: you add a link before adding a room");
        else if (ft_strchr(map->content, '-') && rooms)
            *links = validate_link(map->content, *links, *rooms);
        else if (!ft_strncmp(map->content, "#", 1))
            ;
        else
        {
            *rooms = validate_room(map->content, *rooms, start_end, *links);
            start_end ? (start_end = 0) : start_end;
        }
        map = map->next;
    }
}

t_list *create_ants(int num_of_ants, t_list *start_room)
{
    t_list *head;
    t_ant  *ant;
    t_list *new;

    head = NULL;
    while (num_of_ants)
    {
        ant = (t_ant *)malloc(sizeof(t_ant));
        ant->ant = num_of_ants;
        ant->room = start_room;
        new = ft_lstnew(ant, sizeof(t_ant));
        head = add_to_the_end_of_list(head, new);
        num_of_ants--;
    }
    return (head);
}

t_link *create_link(t_room *room_one, t_room *room_two)
{
    t_link *link;

    link = (t_link *)malloc(sizeof(t_link));
    link->r1 = room_one;
    link->r2 = room_two;
    return (link);
}
t_room *create_room(char *name, int x, int y, int start_end)
{
    t_room *room;

    room = (t_room *)malloc(sizeof(t_room));
    room->x = x;
    room->y = y;
    room->name = name;
    room->is_start = (start_end == 1 ? 1 : 0);
    room->is_end = (start_end == 2 ? 1 : 0);
    return (room);
}

