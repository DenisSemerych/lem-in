#include "lem_in.h"

t_list *last_elem(t_list *head)
{
    while(head && head->next)
        head = head->next;
    return (head);
}

