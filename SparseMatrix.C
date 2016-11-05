#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  int row;
  int col;
  struct node* right;
  struct node* down;
} node_t;

typedef struct matrix{
  int rows;
  int cols;
  node_t* head;
} matrix_t;

node_t* createNode(int row, int col, int data){
  node_t* newnode = (node_t*) malloc(sizeof(node_t));
  newnode->row    = row;
  newnode->col    = col;
  newnode->data   = data;
  newnode->right  = NULL;
  newnode->down   = NULL;
  return newnode;
}

int insertNode(matrix_t* A, int row, int col, int data){
  node_t *col_marker, *row_marker, *temp, *newnode, *extra;

  if (A->rows -1 < row || A->cols-1 < col || row<0 || col<0)
  {
    return 0;
  }

  else{
    col_marker = A->head;
    row_marker = A->head;

    while(col_marker->col!= col){
      col_marker = col_marker->right;
    }

    while(row_marker->row!= row){
      row_marker = row_marker->down;
    }

    newnode = createNode(row, col, data);

    if(row_marker->right == NULL){
      row_marker->right = newnode;
    }

    else{
      temp = row_marker->right;

      while(temp->right!=NULL && temp->right->col<col){
        temp = temp->right;
      }

      extra          = temp->right;
      temp->right    = newnode;
      newnode->right = extra;
    }

    if(col_marker->down==NULL){
      col_marker->down = newnode;
    }
    else{
      temp = col_marker->down;
      while(temp->down!=NULL && temp->down->row<row){
        temp = temp->down;
      }

      extra         = temp->down;
      temp->down    = newnode;
      newnode->down = extra;
    }
  }

  return 1;
}

matrix_t* createMatrix(int rows, int cols){
  int i;
  node_t* temp;
  matrix_t* A = (matrix_t*) malloc(sizeof(matrix_t));
  A->rows     = rows;
  A->cols     = cols;

  A->head        = (node_t*) malloc(sizeof(node_t));
  A->head->down  = NULL;
  A->head->right = NULL;
  A->head->row   = -1;
  A->head->col   = -1;

  temp = A->head;

  for(i=0; i<cols; i++){
    temp->right        = (node_t*) malloc(sizeof(node_t));
    temp->right->col   = i;
    temp->right->row   = -1;
    temp->right->right = NULL;
    temp->right->down  = NULL;
    temp               = temp->right;
  }
  temp->right = NULL;

  temp = A->head;

  for(i=0; i<rows; i++){
    temp->down        = (node_t*) malloc(sizeof(node_t));
    temp->down->row   = i;
    temp->down->col   = -1;
    temp->down->right = NULL;
    temp->down->down  = NULL;
    temp              = temp->down;
  }

  temp->down = NULL;
  return A;
}

void getMatrixData(matrix_t* A){
  int rows = A->rows;
  int cols = A->cols;
  int i, j, x;

  for(i =0; i<rows; i++){
    for(j=0; j<cols; j++){
      printf("%d, %d: ", i, j);
      scanf("%d", &x);
      if(x!=0){
        insertNode(A, i, j, x);
      }
    }
  }
}

void display(matrix_t* A){
  node_t* temp = A->head->down;
  node_t* other;
  int curCol = -1;
  printf("\nPrinting matrix\n");

  while(temp!=NULL){
    other = temp->right;
    printf("Row %d:\t", temp->row);
    curCol = -1;
    while(other!=NULL){
      ++curCol;
      if(other->col!=curCol){
        while(curCol<other->col){
          printf("0\t");
          ++curCol;
        }
      }

      printf("%d\t", other->data, other->col);
      other = other->right;
    }
    ++curCol;

    if(curCol<A->cols){
      while(curCol<A->cols){
        printf("0\t");
        ++curCol;
      }
    }

    printf("\n");

    temp = temp->down;
  }
}

matrix_t* add(matrix_t* A, matrix_t* B){
  node_t *Aptr , *Bptr, *tempA,*tempB;
  matrix_t* C;

  if(A->rows!= B->rows || A->cols != B->cols){
    printf("\nERROR: Invalid matrices for addition\n");
    return NULL;
  }

  C = createMatrix(A->rows, A->cols);

  Aptr= A->head->down;
  Bptr= B->head->down;

  while(Aptr!=NULL){
    tempA = Aptr->right;
    tempB = Bptr->right;

    while(tempA!=NULL && tempB!=NULL){
      if(tempA->col == tempB->col){
        insertNode(C, tempA->row, tempA->col, tempA->data+tempB->data);
        tempA= tempA->right;
        tempB= tempB->right;
      }

      else if(tempA->col<tempB->col){
        insertNode(C, tempA->row, tempA->col, tempA->data);
        tempA= tempA->right;
      }

      else{
        insertNode(C, tempB->row, tempB->col, tempB->data);
        tempB= tempB->right;
      }
    }

    if(tempA==NULL && tempB!= NULL){
      while(tempB!=NULL){
        insertNode(C, tempB->row, tempB->col, tempB->data);
        tempB= tempB->right;
      }
    }

    if(tempB==NULL && tempA!=NULL){
      while(tempA!=NULL)
      {
        insertNode(C, tempA->row, tempA->col, tempA->data);
        tempA= tempA->right;
      }
    }

    Aptr= Aptr->down;
    Bptr= Bptr->down;
  }

  return C;
}

int main(){
  matrix_t* A;
  matrix_t* B;
  matrix_t* C;
  int m, n;

  printf("Enter dimensions of first matrix:\t");
  scanf("%d %d", &m, &n);
  A= createMatrix(m, n);
  getMatrixData(A);

  printf("Enter dimensions of second matrix:\t");
  scanf("%d %d", &m, &n);
  B= createMatrix(m, n);
  getMatrixData(B);

  printf("\nFirst matrix:\n");
  display(A);

  printf("\nSecond matrix:\n");
  display(B);

  C= add(A, B);
  printf("\nAddition of both matrices:\n");
  display(C);

  return 0;
}
