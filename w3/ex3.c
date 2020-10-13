#include "stdio.h"
#include <stdlib.h>

struct node 
{ 
  int v; // value in that node
  struct node *right; // next node
}; 

/**
  n is the linked list object
  */
void print_list(struct node *n)
{
  while (n != NULL)
  {
    printf("%d ", n->v);
    n = n->right;
  }
}

/**
  creates and inserts a new node with value v to the right of node n_left
  */
void insert_node(int v, struct node** n_left)
{
  struct node* n = (struct node*) malloc(sizeof(struct node)); 
  n->v = v; 

  // if there's no head yet, create one
  if ((*n_left) == NULL)
  {
    (*n_left) = n;
    return;
  }

  n->right = (*n_left)->right;
  (*n_left)->right = n;
}

void delete_node(int index, struct node **n)
{
  // assuming the head exists
  struct node* cur = *n;
  // if we're asked to delete the first element
  if (index == 0)
  {
    // we re-link the nodes
    *n = cur->right;
    // delete
    free(cur);
    return;
  }
  // we get to our index
  int i = 0;
  while (cur != NULL && i < index - 1)
  {
    cur = cur->right;
    i++;
  }
  // assuming the request is valid and no shenanigans from the user as I don't consider the case of the element not existing
  struct node *r = cur->right->right;
  // deleting
  free(cur->right);
  // re-linking
  cur->right = r;
}

int main(void)
{
  struct node* head = NULL;

  insert_node(11, &head);
  insert_node(12, &head);
  insert_node(1, &head);
  insert_node(12, &head);
  insert_node(2, &(head->right));
  delete_node(0, &head);
  delete_node(2, &head);

  printf("List ");
  print_list(head);

  return 0;
}
