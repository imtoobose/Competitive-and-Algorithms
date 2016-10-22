#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struct definitions for the Huffman tree
   The nodes hold a character array, length of the character array,
    the priority associated with that node, and pointers to right and left
    child
*/

typedef struct node{
  char* data;
  int len;
  int priority;
  struct node* left;
  struct node* right;
} node_t;

typedef struct tree{
  node_t* root;
} tree_t;

/* Struct definitions for priority queue (linked list)
   Every node has a priority and links to its next node
*/

typedef struct qnode{
  node_t* data;
  int priority;
  struct qnode* next;
} qn_t;

typedef struct q{
  qn_t* head;
} q_t;

//Function prototypes

//Struct initialization functions
node_t* createTreeNode(char[10], int, int);
qn_t* createQNode(node_t*, int, qn_t*);

//Queue functions
void insertInQ(q_t*, node_t*);
int empty(q_t*);
node_t* pop(q_t*);
void display(q_t*);

//Huffman tree functions
void displayTree(node_t*);
void getCode(node_t*, char, int [20], int, int);
void decipher(node_t*, int [20], int);
node_t* makeHuffman(q_t*, const char [], const int [], int);

//End of prototypes

//Main function
int main(){
  //Initializing data
  int n, i, declen, allbreak=0, choice;
  char ch;
  node_t* root;
  int code[20], dec[20];
  static char hello[100];
  static int freq[100];

  for(i=0; i<20; i++) code[i]= 0;

  q_t* qq = (q_t*) malloc(sizeof(q_t));
  qq->head=NULL;
  //End of initialization

  //Get character array
  printf("Enter the elements\n");
  scanf("%s", hello);

  //Get priorities
  printf("\nEnter frequency of above elements\n");
  for(i=0; i<strlen(hello); i++){
    printf("%c: ", hello[i]);
    scanf("%d", &freq[i]);
  }

  //Create the Huffman tree
  root = makeHuffman(qq, hello, freq, strlen(hello));

  //Get Code for all generated values
  printf("The generated codes are:\n");
  for(i=0; i<strlen(hello); i++) {
    printf("%c: ", hello[i]);
    getCode(root, hello[i], code, 0, 0);
  }

  while(1){
    printf("MENU\n1. Decipher a code\n2. Get code for a character\n3. Exit\n");
    scanf("%d", &choice);
    switch(choice){
      case 1:
        printf("Enter length of code\n");
        scanf("%d", &declen);
        printf("Enter the code: ");
        for(i=0; i<declen; i++)
          scanf("%d", &dec[i]);
        decipher(root, dec, declen);
        break;
      case 2:
        printf("Enter character to encode\n");
        scanf(" %c", &ch);
        getCode(root, ch, code, 0, 0);
        break;
      case 3:
        allbreak = 1;
        break;
      default: printf("Invalid value\n");
    }
    if(allbreak) break;
  }

return 0;
}

//Create a tree node
//Assign a character array, array's length and the priority
node_t* createTreeNode(char val [10], int len, int priority){
  int i;
  node_t* newnode= (node_t*) malloc(sizeof(node_t));

  char* x = (char*) malloc(10);
  for(i=0; i<len; i++) x[i] = val[i];

  newnode->len = len;
  newnode->data = x;
  newnode->priority = priority;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}

//Create a priority queue node
//Assign the tree node stored in it
//The priority of the queue node
//The next node in the list
qn_t* createQNode(node_t* val, int priority, qn_t* next){
  qn_t* newnode= (qn_t*) malloc(sizeof(qn_t));
  newnode->data = (val);
  newnode->priority = priority;
  newnode->next = next;
  return newnode;
}

//Insert in linked list queue according to priority
void insertInQ(q_t* qq, node_t* val){
  qn_t* newQnode, *temp;

  if(qq==NULL) return;

  newQnode = createQNode(val, val->priority, NULL);

  //Empty queue
  if(empty(qq)){
    qq->head = newQnode;
    return;
  }

  //If the top of queue has greater priority, then assign new node
  //to top of queue
  if(qq->head->priority >= newQnode->priority){
    temp = qq->head;
    newQnode->next = temp;
    qq->head = newQnode;
    return;
  }

  temp = qq->head;

  //Loop till we find the position just before the new node should be
  //inserted. Otherwise loop till the end
  while(temp ->next!=NULL && temp->next->priority <= val->priority){
    temp= temp->next;
  }

  //If inserting at end
  if(temp->next == NULL){
    temp->next = newQnode;
    return;
  }

  //Inserting anywhere in the middle of the list
  else{
    newQnode->next = temp->next;
    temp->next = newQnode;
    return;
  }
}

//Pop top of queue
node_t* pop(q_t* qq){
  node_t* ans;
  qn_t* temp;
  int i;
  if(empty(qq)) return NULL;

  else{
    ans = qq->head->data;
    temp = qq->head;
    qq->head = qq->head->next;
    free(temp);
    return ans;
  }
}

//Check if queue is empty
int empty(q_t* qq){
  if(qq==NULL || qq->head==NULL) return 1;
  else return 0;
}

//Display the queue
void display(q_t* qq){
  qn_t* temp= qq->head;

  int i;
  while(temp!=NULL){
    for(i=0; i<temp->data->len; i++){
      printf("\n(%c", temp->data->data[i]);
    }

    printf(" %d)\t", temp->priority);
    temp= temp->next;
  }
return;
}

//Make a huffman tree using priority queue
node_t* makeHuffman(q_t* qq, const char p [], const int f[], int len){
  int i;
  char x[10];
  node_t* left, *right, *newnode;

  //Create leaf nodes for all characters in the array
  for(i=0; i<len; i++){
    x[0] = p[i];
    newnode= createTreeNode(x, 1, f[i]);
    insertInQ(qq, newnode);
  }

  //Loop till queue is empty
  //At every iteration pop first two elements
  //Create a root that holds the aggregate value of these elements
  //It's priority is the addition of priority of the top elements
  //Attach the first popped element to the left of this new node
  //Second to the right of this new node
  //Then, reinsert this node in the priority queue
  //Iteration stops when only one element is left in the list
  //This will be the root node of the Huffman tree

  while(!empty(qq)){
    left = pop(qq);
    right = pop(qq);

    if(right==NULL) break;

    for(i=0; i<left->len; i++) x[i] = left->data[i];
    for(i=0; i<right->len; i++) x[i+left->len]= right->data[i];

    newnode = createTreeNode(x,
                             left->len+ right->len,
                             left->priority + right->priority);
    newnode->left = left;
    newnode->right = right;

    insertInQ(qq, newnode);
  }

  return left;
}

//Inorder traversal and display of generated Huffman tree
void displayTree(node_t* root){
  int i;
  if(root==NULL) return;

  displayTree(root->left);

  for(i=0; i<root->len; i++)
   printf("%c ", root->data[i]);
  printf("\n");

  displayTree(root->right);
}

//Get the code of a certain character
//As all characters will be leaf nodes, this is the base
//case of the recursion. If a leaf node matches searched value,
//we print the code generated

void getCode(node_t* root, char val, int code[20], int lenOfCode, int index){
  int i;
  if(root->left==NULL && root->right==NULL){
    if(root->data[0] == val){
      for(i=0; i<lenOfCode; i++) printf("%d", code[i]);
      printf("\n");
    }
    else{
      return;
    }
  }

  else{
    //When going left, 0 is the code
    code[index] = 0;
    getCode(root->left, val, code, lenOfCode + 1, index + 1);
    //When going right, 0 is the code
    code[index] = 1;
    getCode(root->right, val, code, lenOfCode + 1, index + 1);
  }
}

//Decipher a binary code using Huffman tree
void decipher(node_t* root, int code[20], int len){
  node_t *temp;
  int i;
  if(root==NULL) printf("No encoding tree exists\n");
  temp = root;
  for(i=0; i<len; i++){
    if(temp==NULL){
      printf("Invalid code\n");
      return;
    }
    if(code[i]==0){
      temp= temp->left;
    }
    if(code[i]==1){
      temp= temp->right;
    }
  }

  if(temp->left==NULL && temp->right==NULL){
    printf("Deciphered: %c\n", temp->data[0]);
  }
  else{
    printf("Invalid code\n");
  }
}
