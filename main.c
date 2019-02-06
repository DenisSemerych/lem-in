#include "lem_in.h"

t_list *add_to_the_end_of_list(t_list *head, t_list *new)
{
    t_list *crawler;

    crawler = head;
    if (!crawler)
        return (new);
    while(crawler->next)
        crawler = crawler->next;
    crawler->next = new;
    return (head);
}

int main (int argc, char **argv)
{
    char *line;
    t_list *map;
    t_list *new;

    while (get_next_line(0, &line))
    {
        new = ft_lstnew(NULL, 0);
        new->content = line;
        map = add_to_the_end_of_list(map, new);
    }
    if (!map)
        put_err_msg_exit("Usage: you need to give a valid map");
    validate(map);
    system("leaks libft");
}
