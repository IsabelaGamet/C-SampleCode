
// bst.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "KindredSpirits.h"

node *BST_insert(node *root, int data) // The output is a node
{
    // If empty create node. This is the base case. If there is a space, add node here
    if (root == NULL)
        root = createNode(data);
    // Insert in left subtree
    else if(data < root->data)
        root->left = BST_insert(root->left, data); // this way the recursive call updates the left pointer, not the root pointer

    else if(data > root->data)
        root->right = BST_insert(root->right, data);

    // disallow insert duplicates
    else
        ;

    return root;
}


// print the pre-order tree traversal
void preorder(node *root)
{
    if(root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
// print the in-order tree traversal
void inorder(node *root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
// print the post-order tree traversal
void postorder(node *root)
{
    if(root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
int max(int a, int b)
{
    return (a >= b) ? a : b;
}

// A recursive function that finds the height of the binary tree
int height(node *root)
{
    // Base case
    if (root == NULL)
        return -1;
    return 1 + max(height(root->left), height(root->right));
}

// Recursively frees all nodes in the binary tree
// It's supposed to be called forest_fire or freeTree I changed the name
node *freeTheTreesFromVeganistTyranny(node *root)
{
    // Base case
    if (root == NULL)
        return NULL;

    freeTheTreesFromVeganistTyranny(root->left);
    freeTheTreesFromVeganistTyranny(root->right);

    free(root);
    return NULL;
}

// Recursive function that finds max element in the tree
int findMax(node *root)
{
    if (root->right == NULL)
        return root->data;

    return findMax(root->right);
}

// Delete Data from BST
node *BST_delete(node *root, int data)
{
    node *newRoot;

    // Base case
    if (root == NULL)
        return NULL;

    // if the key I am looking for is less than root->Data
    // I have to look for it in the left subtree
    if (data < root->data)
        root->left = BST_delete(root->left, data);

    else if (data > root->data)
        root->right = BST_delete(root->right, data);

    else
    {
        // HOORAY! We have found the data that has to be removed
        if (root->left == NULL && root->right == NULL) // doesn't have any children
        {
            free(root);
            root = NULL;
            //return NULL;
        }
        else if (root->right == NULL) // means it has just a left child
        {
            newRoot = root->left;
            free(root);
            return newRoot;
        }
        else if(root->left == NULL)
        {
            newRoot = root->right;
            free(root);
            return newRoot;
        }
        else
        {
            // This is the case that we have two children for the root
            // We have to find the max value on the left subtree of this node
            root->data = findMax(root->left);
            root->left = BST_delete(root->left, root->data);
        }
    }
}

// Takes the root of a bst and returns a pointer to the node with max value
node *largest(node *root)
{
    // Base case
    if (root == NULL)
        return NULL;

    if(root->right == NULL) // if there are no children to the right
        return root;

    return largest(root->right);
}

// Can I make this recursive function to work based on iterative approach?
node *iterativeLargest(node *root)
{
    if(root == NULL)
        return NULL;

    while(root->right != NULL)
        root = root->right;

    return root;
}

// A recursive function that counts the number of nodes in the tree?
int countNodes(node *root)
{
    return (root == NULL) ? 0 : 1 + countNodes(root->left) + countNodes(root->right);
}
/*
// How can I use stack to count how many nodes I have in my tree?
int countNodesIterative(node *root)
{
    int count = 0;
    Stack *s = magicalStack();
    push(s, root);

    while(!isEmpty(s))
    {
        root = pop(s);
        if(root != NULL)
        {
            count++;
            push(s, root->left);
            push(s, root->right);
        }
    }

    return count;
}*/


// a recursive function that compares two trees and returns if trees are different
int treeDiff(node *a, node *b)
{
    if (a == NULL && b == NULL)
        return 0;
    else if(a->data != b->data)
        return 1;
    else if(a == NULL || b == NULL)
        return 1;

    return treeDiff(a->left, b->left) || treeDiff(a->right, b->right);
}

int main(void)
{
    int i, r, n = 0;
    node *root = NULL, *root2;

    srand(time(NULL));

    /*for(i = 0; i < 10; i++)
    {
       printf("Inserting %d...\n", r = rand() % 50 + 1);
       root = BST_insert(root, r);
    }*/

    printf("Inserting %d...\n", r = 28);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 49);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 6);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 31);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 23);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 4);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 3);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 16);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 7);
    root = BST_insert(root, r);

    printf("Inserting %d...\n", r = 11);
    root = BST_insert(root, r);



    printf("Preorder:  ");
    preorder(root);

    printf("\nInorder:   ");
    inorder(root);

    printf("\nPostorder: ");
    postorder(root);

    printf("\nroot2\n");

    root2 = makeReflection(root);
    printf("Preorder:  ");
    preorder(root2);

    printf("\nInorder:   ");
    inorder(root2);

    printf("\nPostorder: ");
    postorder(root2);


    printf("\nIs it reflection or nah? %d", isReflection(root, root2));

    //printf("\nIs it equal or nah? %d", isEqual(root, root2));





    return 0;
}
