#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fibdata;
   struct node* next;
};
int get_len(struct node *p);

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {

      x = fib(n - 1);

      y = fib(n - 2);

	  return (x + y);
   }
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = (struct node*)malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  =  (struct node*)malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}
int get_len(struct node *p){
  int len = 0;
  while(p){
    p = p->next;
    len++;
  }
  return len;
}
int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     
	 printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N+1,FS);      
 
     p = init_list(p);
     head = p;
	 int list_len = get_len(p);
	 struct node *ptr_ary[list_len];
	 int i;
	 for(i = 0; i < list_len; i++)
	 {
	   ptr_ary[i] = p;
	   p = p->next;
	 }
     start = omp_get_wtime();
     #pragma omp parallel
     {
        #pragma omp for schedule(static,1)
        for(i = 0; i < list_len; i++){
          processwork(ptr_ary[i]);
        }
     }

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}

