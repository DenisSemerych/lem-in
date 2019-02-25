#include "lem_in.h"

t_list *last_elem(t_list *head)
{
    while(head && head->next)
        head = head->next;
    return (head);
}

void del_last(t_list **head)
{
    t_list *crawler;

    crawler = *head;
    while(crawler && crawler->next && crawler->next->next)
        crawler = crawler->next;
    crawler && crawler->next ? (crawler->next = NULL) :
    (*head = NULL);
}

//t_room *reverse_hash_function(int index, t_list *hash_table)
//{
//    while(hash_table)
//    {
//        if (hash_table->content_size == index)
//            return ((t_room *)hash_table->content);
//        hash_table = hash_table->next;
//    }
//    put_err_msg_exit("Error: something went wrong while working with reverse hash-function");
//    return (NULL);
//}