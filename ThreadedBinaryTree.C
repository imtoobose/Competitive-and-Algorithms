#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int data;
    int rightSuccessor;
    struct node* left;
    struct node* right;
} node_t;

typedef struct tree{
    node_t* root;
} tree_t;

node_t* getParent(tree_t* T, int search){
    node_t* temp, *pred;
    temp= T->root;

    while(temp!=NULL){
        pred = temp;
        if(temp->data> search){
            temp=temp->left;
        }
        else{
            if(!temp->rightSuccessor)
                temp=temp->right;
            else
                break;
        }
    }
    return pred;
}

node_t* createNode(int data){
    node_t* temp         = NULL;
    temp                 = (node_t*) malloc(sizeof(node_t));
    temp->rightSuccessor = 0;
    temp->right          = NULL;
    temp->left           = NULL;
    temp->data           = data;
    return temp;
}

void insertNode(tree_t* T, int data){
    node_t *par, *temp, *newnode;
    if(T->root==NULL){
        T->root= createNode(data);
        T->root->rightSuccessor = 0;
        T->root->left = NULL;
        T->root->right = NULL;
        return;
    }

    temp    = T->root;
    newnode = createNode(data);
    par     = getParent(T, data);

    if(par->data > newnode->data){
        par->left               = newnode;
        newnode->rightSuccessor = 1;
        newnode->right          = par;
    }

    else{
        newnode->right = par->right;
        par->right     = newnode;
        if(newnode->right!=NULL)
          newnode->rightSuccessor = 1;
        par->rightSuccessor = 0;
    }
}

node_t* deleteNode(node_t* root, int find){
  node_t *temp, *par, *extra;
  int path = 0;

  par= root;
  temp= root;
  if(root==NULL) return root;
  //Find the node
  while(1){
    if(find== temp->data){
      break;
    }

    if(temp->data> find){
      if(temp->left == NULL) return root;
      par = temp;
      temp = temp->left;
      path = 0;
    }
    else{
      if(temp->rightSuccessor || temp->right==NULL) return root;
      par = temp;
      temp = temp->right;
      path = 1;
    }
  }

  //1. No child
  if( (temp->rightSuccessor || temp->right==NULL) && temp->left==NULL){
    if(par!=temp){
      if(path==0) par->left = NULL;
      else par->right = NULL;
    }

    if(temp==par){
      free(temp);
      return NULL;
    }

    free(temp);
    return root;
  }

  //Right child present
  else if( temp->left==NULL ){
    if(path==0){
      par->left = temp->right;
    }

    else{
      par->right = temp->right;
    }
    
    free(temp);
    return root;
  }

  //Left child present
  else if( temp->right==NULL || temp->rightSuccessor){
    if(temp->rightSuccessor && temp->left->rightSuccessor)
      temp->left->right = temp->right;

    if(temp->right==NULL && temp->left->rightSuccessor){
      temp->left->rightSuccessor = 0;
      temp->left->right = NULL;
    }

    if(path==0){
      par->left = temp->left;

    }

    else{
      par->right = temp->left;
    }

    free(temp);
    return root;
  }

  else{
    extra = temp->right;
    while(extra->left!=NULL){
      extra = extra->left;
    }

    root->data  = extra->data;
    root->right = deleteNode(root->right, extra->data);
    return root;
  }
}

void display(tree_t* T){
  node_t* temp= T->root;
  int i=0;

  while(temp->left!=NULL){
    temp=temp->left;
  }

  while(temp!=NULL){
    printf("%d\t", temp->data);
    if(temp->rightSuccessor)
      temp=temp->right;

    else{
      temp= temp->right;
      if(temp==NULL) break;
      while(temp->left!=NULL){
        temp= temp->left;
      }
    }
  }
}

int main(){
    int choice, innerchoice, allbreak=0;
    tree_t* T = (tree_t*) malloc(sizeof(tree_t));
    T-> root = NULL;
    insertNode(T, 5);
    insertNode(T, 7);
    insertNode(T, 3);
    T->root= deleteNode(T->root, 3);
    //display(T);

    while(1){
      printf("\n=======MENU========\n1. Enter an element\n2. Delete an element\n3. Display tree\n4.Exit\n");
      scanf("%d", &choice);
      switch(choice){
        case 1:
          printf("\nEnter data:\t");
          scanf("%d", &innerchoice);
          insertNode(T, innerchoice);
          break;
        case 2:
          printf("\nEnter data:\t");
          scanf("%d", &innerchoice);
          T->root = deleteNode(T->root, innerchoice);
          break;
        case 3:
          display(T);
          break;
        case 4: allbreak =1; break;
        default: printf("\nInvalid choice!\n");
      }
      if(allbreak) break;
    }
    return 0;
}
