#include "head.h"
#ifndef _MY_HEADER
#define _MY_HEADER
#define ERROR_MSG(msg) printf("ERROR:"#msg "\n");
//The basic record of a congestion sequence
//does not include other important info such as
//day, location, etc.
typedef struct basic_record{
	char *seq;			//e.g. "lmhm", "nll"
	int sup;			//support
}*elemType;				//points to a record
//node in the linked list
typedef struct lnode{
	elemType data;		//points to a record
	struct lnode *next;	
	struct lnode *prev;
}*lnode_ptr,lnode;			
//linked list structure
typedef struct{
	lnode_ptr head;		//points to first node
	lnode_ptr tail;		//points to last node
	int len;			//number of elements
}linked_list;
#endif
int isEmpty(linked_list * list){
    return !(list->len);
}
lnode_ptr make_node(elemType e){//given a record(ptr), returns what a node in double linked list
    lnode_ptr ptr = (lnode_ptr)malloc(sizeof(lnode));
    if(!ptr){
        ERROR_MSG(No free space to allocate!)
        return NULL;
    }
    else{
        ptr->data = e;
        ptr->next = ptr;   
        ptr->prev = ptr;
        return ptr; 	
    }
}
//frees the space ptr points to 
//remember that ptr itself is not set null--
//we only have a copy of it
void free_node(lnode_ptr ptr){
    if(ptr){
        if(ptr->data){
            if(ptr->data->seq){
                free(ptr->data->seq);
                ptr->data->seq = NULL;   
            }
            free(ptr->data);
            ptr->data = NULL;
        }
        free(ptr);
    }
    else
    	ERROR_MSG(NullPtr_no need to free!)
}

linked_list * init_list(){
    linked_list *ptr = (linked_list *)malloc(sizeof(linked_list));
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->len = 0;
    return ptr;
}
//given a linked list and a node
//insert the node into the head of the list
int ins_first(linked_list *list, lnode_ptr node_ptr){
    if(!list){
        ERROR_MSG(List does not exist)
        return -1;
    }
    if(!node_ptr){
        ERROR_MSG(node does not exist)
        return -1;
    }
    if(list->len == 0){
        list->head = node_ptr;
        list->tail = node_ptr;
    }  
    else{ 
		list->head->prev = node_ptr;
		list->tail->next = node_ptr; 
		node_ptr->next = list->head;
		node_ptr->prev = list->tail;
		list->head = node_ptr;
	}
	list->len++;
	return 0;
}
//already know the addr of the sequence(node) we would like to delete
//assume node_ptr is in list
//just do it!
int del_node(linked_list *list, lnode_ptr node_ptr){
    assert(list->len >= 1);
    if(list->len >= 2){
        node_ptr->next->prev = node_ptr->prev;
        node_ptr->prev->next = node_ptr->next;
        if(list->head == node_ptr)
            list->head = node_ptr->next;
        if(list->tail == node_ptr)
            list->tail = node_ptr->prev;
    }
    else//ONLY ONE ELEM
       list->head = list->tail = NULL;
    list->len--;
    return 1;
}
