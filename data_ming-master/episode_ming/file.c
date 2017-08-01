#include "head.h"
void print_list_file(linked_list *llptr){
    int list_len = llptr->len;
    lnode_ptr node_ptr;
    int i = 0;
    for(node_ptr = llptr->head; i < list_len; i++){
        print_node_file(node_ptr);
        node_ptr = node_ptr->next;
    }
}
void print_node_file(lnode_ptr p){
    printf("pattern:%s\t",p->data->seq);
    printf("support:%d\n",p->data->sup); 
}
