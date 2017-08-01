#include "head.h"

linked_list* Candidates[MAX_SEQ_LEN];
char * get_string(lnode_ptr node);

void build_C_from_FEi(int i);
char *linkable(char *s, char *t);
lnode_ptr get_head(linked_list *list);
int get_length(linked_list *list);
char *get_elem_SD(int i);
stream_database SD;
int count_sup(char *t, char *w);


void init(){
    int i;
    extern char *cong_level_set[4];
    for(i = 0; i < MAX_SEQ_LEN; i++)
        Candidates[i] = init_list();
    for(i = 0; i < NUM_OF_CONG_LEVEL; i++)
        ins_first(Candidates[0],make_node(string_to_record(cong_level_set[i])));
}
void generate_SD(){
    extern stream_database SD;
    extern char *cong_level_set[4];
    int i,j;
    //printf("%c\n\n\n",cong_level_set[rand()%(NUM_OF_CONG_LEVEL)][0]);
    for(i = 0; i < NUM_STREAM; i++){
        for(j = 0; j < STREAM_LEN; j++){
            SD[i][j] = cong_level_set[rand()%(NUM_OF_CONG_LEVEL)][0];
        }
    }
}
void freq_episode_mining(){
    time_t second_start = time(NULL);
    init();
    int i = 0;
    char *s,*c;
    int stream;
    int seq_traversed;
    lnode_ptr cnode;
    lnode_ptr temp_cnode;
    int length;
    //testing github
    while(i <MAX_SEQ_LEN && !isEmpty(Candidates[i]) ){      
        
        for(stream = 0; stream < NUM_STREAM; stream++){
            s = get_elem_SD(stream);
            for(cnode = get_head(Candidates[i]), seq_traversed = 0, length = get_length(Candidates[i]); seq_traversed < length; cnode = cnode->next){
                c = get_string(cnode);
                cnode->data->sup += count_sup(s,c);
                seq_traversed++;
            }    
        }
        //identify frequent episodes
        for(cnode = get_head(Candidates[i]), seq_traversed = 0; seq_traversed < length; cnode = temp_cnode){
            c = get_string(cnode);
            temp_cnode = cnode->next;
            if(cnode->data->sup < min_fr) {del_node(Candidates[i],cnode); free_node(cnode);}
            seq_traversed++;
        }
        if(isEmpty(Candidates[i]))
            break;
        print_list_file(Candidates[i]);
        if(i < MAX_SEQ_LEN - 1)//if i == MAX - 1, should not build further
        	build_C_from_FEi(i);
        i++; 
    }
    time_t second_end = time(NULL);
    printf("%ld\n",second_end - second_start);
}
void build_C_from_FEi(int i){
    if(isEmpty(Candidates[i]))//empty list, should not be null
        return;
    int len = get_length(Candidates[i]);
    lnode_ptr cnode_i;
//    lnode_ptr cnode_j;
    char *s;
    char *ci,*cj;
    int seq_traversed_i,seq_traversed_j;
    lnode_ptr ugly_array[len];
    for(cnode_i = Candidates[i]->head, seq_traversed_i = 0; seq_traversed_i < len; cnode_i = cnode_i->next){
        ugly_array[seq_traversed_i] = cnode_i;
        seq_traversed_i++;
    }
//    printf("1");
    #pragma omp parallel for collapse(2) default(none) shared(len,Candidates,i) private(ci,cj,s) shared(ugly_array)
    for(seq_traversed_i = 0; seq_traversed_i < len; seq_traversed_i++){
        for(seq_traversed_j = 0; seq_traversed_j < len; seq_traversed_j++){
//        printf("thread num:%d\n",omp_get_thread_num());
            if(seq_traversed_i == seq_traversed_j)
                continue;
            
            ci = ugly_array[seq_traversed_i]->data->seq;
            cj = ugly_array[seq_traversed_j]->data->seq;
            s = linkable(ci,cj);
            if(s){
            #pragma omp critical
            {
                ins_first(Candidates[i + 1],make_node(string_to_record(s)));
            }
            }
        }
    } 
}
char * get_string(lnode_ptr node){
    return node->data->seq;
}

char *linkable(char *s, char *t){
    char *ret;
    if(s[1] == 0)//two single state sequences, i.e. "l" and "m"
    {
        assert(t[1] == 0);
        ret = (char *)malloc(3);
        ret[0] = s[0];
        ret[1] = t[0];
        ret[2] = 0;
        return ret;

    }
    int i = 0;
    while(s[i + 1] == t[i] && s[i + 1] != 0 && t[i] != 0)//sequence len >= 2, match
        i++;
    if(s[i + 1] == 0){//e.g. "abcde" and "bcdef"
        assert(t[i + 1] == 0);
        ret = (char *)malloc((size_t) i + 2);
        ret[i + 2] = 0;
        ret[i + 1] = t[i];
        while(i >= 0){
            ret[i] = s[i];
            i--;
        }
        return ret;
    }
    else
        return NULL;
}
lnode_ptr get_head(linked_list *list){
    assert(list !=NULL);
    assert(list->head != NULL);
    return list->head;
}
int get_length(linked_list *list){
    return list->len;
}
char *get_elem_SD(int i){
    extern stream_database SD;
    return SD[i];
}
