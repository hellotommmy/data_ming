#include "head.h"
int count_sup(char *t, char *w){//kmp algo
    int i = 0;
    int j = 0;
    int offset;
    int count = 0;
    while(t[i]!=0){
        j = 0;
        offset = 0;
        while(t[i] == w[j]){
            i++;
            j++;
            offset++;
            if(w[j] == 0)
            {
                count++;
                break;
            }
       }
       i -= offset;
       i++;
    }
    return count;
    
}
void print_database(){
    extern stream_database SD;
    int i;
    for(i = 0; i < NUM_STREAM; i++)
        printf("%s\n",SD[i]);
}
void print_node(lnode_ptr ptr){
    if(!ptr)
        ERROR_MSG(node does not exist)
    else{
        printf("********************list********************\n");
        printf("node addr: 0x%lx\n",(long)ptr);
        printf("next node addr: 0x%lx\n",(long)ptr->next);    
        printf("prev node addr: 0x%lx\n",(long)ptr->prev);  
        printf("points to data node: 0x%lx\n",(long)ptr->data);
        if(ptr->data){
            printf("pattern:%s\n",ptr->data->seq);
            printf("support:%d\n",ptr->data->sup);
        }   
    }
}
