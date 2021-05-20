
#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

#define TRUE 1
#define FALSE 0
#define NUMBER_OF_TREES 5


int main (int numberOfArguments, char* arguments[])
{
  // local variables
  node* trees[NUMBER_OF_TREES];

  // initializes trees[0]
  trees[0] = createNode(10);
  trees[0]->left = createNode(20);
  trees[0]->right = createNode(30);
  trees[0]->right->left = createNode(40);
  trees[0]->right->right = createNode(1);

  // initializes trees[1]
  trees[1] = createNode(10);
  trees[1]->left = createNode(30);
  trees[1]->left->left = createNode(1);
  trees[1]->left->right = createNode(40);
  trees[1]->right = createNode(20);

  // creates reflection tree
  trees[2] = makeReflection(trees[1]);

  // initializes trees[3]
  trees[3] = createNode(23);
  trees[3]->left = createNode(12);
  trees[3]->left->left = createNode(5);
  trees[3]->left->right = createNode(18);
  trees[3]->right = createNode(71);
  trees[3]->right->right = createNode(56);

  // initializes tree[4]
  trees[4] = createNode(56);
  trees[4]->left = createNode(23);
  trees[4]->right = createNode(71);
  trees[4]->right->left = createNode(5);
  trees[4]->right->left->right = createNode(12);
  trees[4]->right->right = createNode(18);

  // shows trees
  for(int i = 0; i < NUMBER_OF_TREES; i++)
  {
    // prints header
    printf("---------------------------------------\n");
    printf("                Tree %d\n", i);
    printf("---------------------------------------\n\n");

    // prints Nodes information
    printNodes(trees[i]);
    printf("\n");

    // prints the number of nodes
    printf("Number of Nodes    : %d \n", countNodes(trees[i]));

    // prints preorder traversal
    printf("Preorder Traversal : ");
    printPreOrderTraversal(trees[i]);
    printf("\n");

    // prints inorder traversal
    printf("Inorder Traversal  : ");
    printInOrderTraversal(trees[i]);
    printf("\n");

    // prints postorder traversal
    printf("Postorder Traversal: ");
    printPostOrderTraversal(trees[i]);
    printf("\n\n");
  }

  // compares trees
  printf("---------------------------------------\n");
  printf("Equality Test:\n");
  printf("---------------------------------------\n\n");
  for(int i = 0; i < NUMBER_OF_TREES-1; i++)
    for(int j = i; j < NUMBER_OF_TREES; j++)
    {
      if (i != j)
      {
        if((isEqual(trees[i], trees[j])) == TRUE)
          printf("Trees[%d] and Trees[%d] are equals. \n", i, j);
        else
          printf("Trees[%d] and Trees[%d] are NOT equals. \n", i, j);
      }
    }
  printf("\n");

  // compares trees
  printf("---------------------------------------\n");
  printf("Reflection Test:\n");
  printf("---------------------------------------\n\n");
  for(int i = 0; i < NUMBER_OF_TREES-1; i++)
    for(int j = i; j < NUMBER_OF_TREES; j++)
    {
      if (i != j)
      {
        if((isReflection(trees[i], trees[j])) == TRUE)
          printf("Trees[%d] and Trees[%d] are reflections. \n", i, j);
        else
          printf("Trees[%d] and Trees[%d] are NOT reflections. \n", i, j);
      }
    }
  printf("\n");

  // compares trees
  printf("---------------------------------------\n");
  printf("Kindred Spirits Test:\n");
  printf("---------------------------------------\n\n");
  for(int i = 0; i < NUMBER_OF_TREES-1; i++)
    for(int j = i; j < NUMBER_OF_TREES; j++)
    {
      if (i != j)
      {
        if((kindredSpirits(trees[i], trees[j])) == TRUE)
          printf("Trees[%d] and Trees[%d] are kindred spirits. \n", i, j);
        else
          printf("Trees[%d] and Trees[%d] are NOT kindred spirits. \n", i, j);
      }
    }
  printf("\n");
}
