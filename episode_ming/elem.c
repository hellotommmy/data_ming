#include "head.h"
elemType string_to_record(char *s){
    elemType e = (elemType)malloc(sizeof(struct basic_record));
    e->seq = (char *)malloc((size_t)(strlen(s) + 1));
    strcpy(e->seq, s);
    e->sup = 0;
    return e;
}
