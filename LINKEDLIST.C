#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
} node_t;

typedef struct list{
  node_t* head;
  int size;
} list_t;

void insert(list_t* ls, int pos, int data){
  node_t* temp = NULL;
  node_t* now;
  node_t* head = ls->head;
  int size     = ls->size;
  int i;

  if(pos<=0 || pos>size+1) {
    printf("\nInvalid position\n");
    return;
  }
  ls->size+=1;
  if(pos==1){
    temp       = (node_t*) malloc(sizeof(node_t));
    temp->next = head;
    temp->data = data;
    ls->head = temp;
  }

  else if(pos==size+1){
    temp = head;
    while( temp->next!=NULL){
      temp = temp->next;
    }
    temp->next       = (node_t*) malloc(sizeof(node_t));
    temp->next->data = data;
    temp             = temp->next;
    temp->next       = NULL;
  }

  else{
    temp = head;
    for(i=1; i<pos-1; i++){
     temp = temp->next;
    }
    now              = temp->next;
    temp->next       = (node_t*) malloc(sizeof(node_t));
    temp->next->data = data;
    temp             = temp->next;
    temp->next       = now;
  }
}

list_t initList(int size){
  list_t ans;
  node_t* temp;
  int i;

  ans.head= (node_t*) malloc(sizeof(node_t));
  ans.head->data = -1;
  ans.size= size;
  temp = ans.head;

  if(size==0) return ans;

  printf("\nInitializing list of size %d\n", size);
  printf("1: ");
  scanf("%d", &(ans.head->data));

  for(i=2; i<=size; i++){
    temp->next = (node_t*) malloc(sizeof(node_t));
    temp = temp->next;
    printf("%d: ", i);
    scanf("%d", &(temp->data));
  }
  temp->next = NULL;
  return ans;
}

void delete(list_t* ls, int pos){
  node_t* temp = ls->head;
  node_t* extra;
  int count;
  
  if (pos<=0 || pos>ls->size){
    printf("\nInvalid position\n");
    return;
  }
  if(ls->size == 0){
    printf("\nEmpty list\n");
    return;
  }
  
  if(pos==1){
    temp = ls->head;
    ls->head = ls->head->next;
    ls->size-=1;
    free(temp);
  }

  else if(pos== ls->size){
    while(temp->next->next !=NULL){
      temp=temp->next;
    }
    extra = temp->next;
    temp->next = NULL;
    ls->size-=1;
    free(extra);
  }

  else{
    count = 1;
    while(temp->next!=NULL && count<pos){
      count+=1;
      temp = temp->next;
    }
    extra = temp->next;
    temp->next = temp->next->next;
    ls->size-=1;
    free(extra);
  }
}

void display(list_t* ls){
  node_t* temp = ls->head;
  int i;
  printf("\n");
  for(i =0; i<ls->size; i++){
    printf("%d\n", temp->data);
    temp = temp->next;
  }
}

int main(){
  list_t a;
  a= initList(0);
  insert(&a, 1, 54);
  insert(&a, 1, 55);
  display(&a);
  delete(&a, 1);
  display(&a);
}
