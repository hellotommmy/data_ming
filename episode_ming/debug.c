#include "head.h"
void test_make_node(){
	elemType e = string_to_record("lmlm");
    lnode_ptr ptr = make_node(e);
    if(ptr)
        print_node(ptr);
    else
        ;
}
void test_make_list(){
    print_list(init_list());
}
void print_list(linked_list *llptr){
    if(llptr){
        int list_len = llptr->len;
        if(list_len == 0){
            printf("empty list\n");
            return;
        }
        lnode_ptr node_ptr;
        int i = 0;
        for(node_ptr = llptr->head; i < list_len; i++){
            print_node(node_ptr);
            node_ptr = node_ptr->next;
        }
    }
    else{
        ERROR_MSG(null is not a list)
    }
}
void test_delete_node(){
	elemType e = string_to_record("lmlm");
    lnode_ptr ptr = make_node(e);
    if(ptr){
        print_node(ptr);
        free_node(ptr);
        ptr = NULL;
        print_node(ptr);
    }    
}
