#ifndef _MY_HEADER
#define _MY_HEADER
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>
#include <time.h>
#define ERROR_MSG(msg) printf(#msg "\n");
#define MAX_SEQ_LEN 8
#define NUM_OF_CONG_LEVEL 4
#define NUM_STREAM 7
#define STREAM_LEN 7
#define min_fr 3
typedef char stream_database[NUM_STREAM + 1][STREAM_LEN + 1];
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

lnode_ptr make_node(elemType e);
void print_node(lnode_ptr ptr);
void print_list(linked_list *llptr);
void print_database();
//take care-- free node must precede setting ptr to NULL!
void free_node(lnode_ptr ptr);
elemType string_to_record(char *s);

//list
linked_list * init_list();
int ins_first(linked_list *list, lnode_ptr node_ptr);
int isEmpty(linked_list * list);
int del_node(linked_list *list, lnode_ptr node_ptr);
void free_node(lnode_ptr ptr);
//init
void init();

void freq_episode_mining();

//file
void print_list_file(linked_list *llptr);
void print_node_file(lnode_ptr p);
#endif

