/********************************************

    Assignment:     Project 3: Kindred Spirits
    Created By:     Isabela C. Rangel   5385
    Class:          Data Structures
    Date created:   06/12/19
    Date modified:  06/16/19

***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"
#define TRUE 1
#define FALSE 0

/*  List of helper functions that will be needed: create node, insert node
    Preorder traversal, preorder traversal inorder traversal*/

// Helper function prototypes
node* createNode              (int data);
void  printPreOrderTraversal  (node *root);
void  printInOrderTraversal   (node *root);
void  printPostOrderTraversal (node *root);
void  printNodes              (node *root);
int   isEqual                 (node *a, node *b);
int   countNodes              (node *root);
void  getPreOrderNodes        (node *root, node* *array);
void  getPostOrderNodes       (node *root, node* *array);

/*      Required Functions      */

/** isReflection function
    Checks if two tree nodes are refections of another.
    @param  a       tree for comparison
    @param  b       tree for comparison
    @return int     returns true or false if a and b are reflections of one another
*/
int isReflection(node *a, node *b)
{
  // consistency: checks if both nodes are null
  if ((a == NULL) && (b == NULL))
  {
    // returns true: both nodes are null
    return TRUE;
  }

  // consistency: checks if only one node is null
  if ((a == NULL) || (b == NULL))
  {
    // returns false: the nodes could not be a reflection
    return FALSE;
  }

  // for trees reflection:
  //  nodes: same values
  //  subnodes: symmetric in structure and values

  // if the data of the nodes are not the same, returns false
  if (a->data != b->data)
      return FALSE;

  // recursively checks if the the subnodes are symmetric reflections
  return (isReflection(a->left, b->right)) && (isReflection(a->right, b->left));
}
/** makeReflection function
    Creates a tree that is the reflection of the input given
    @param  root            node we are trying to make a reflection of
    @return struct node     returns address of newly created reflected tree.
*/
node *makeReflection(node *root)
{
  // variables
  node* reflectedNode;

  // consistency: if the provided node is null, return null
  if (root == NULL)
    return NULL;

  // creates reflected node
  reflectedNode = createNode(root->data);

  // recursively creates left subnode
  reflectedNode->left  = makeReflection(root->right);

  // recursively creates right subnode
  reflectedNode->right = makeReflection(root->left);

  // returns new reflected node
  return reflectedNode;
}

/** Checks if two trees are kindred spirits.
    @param   a     root node of the first tree
    @param   b     root node of the second tree
    @return  int   returns true if the trees are kindred spirits; otherwise, returns false
 */
int kindredSpirits(node *a, node *b)
{
  // variables
  int numberOfNodes;
  node* *arrayA;
  node* *arrayB;

  // counts the number of nodes
  numberOfNodes = countNodes(a);

  // consistency: if the number of nodes is not the same, returns false
  if (numberOfNodes != countNodes(b))
    return FALSE;

  // creates one-dimensional arrays
  arrayA = malloc (numberOfNodes * sizeof(node*));
  arrayB = malloc (numberOfNodes * sizeof(node*));

  // gets the nodes in preorder transversal: a -> arrayA
  getPreOrderNodes(a, arrayA);

  // gets the nodes in postorder transversal: b -> arrayB
  getPostOrderNodes(b, arrayB);

  // compares the elements
  for (int index=0; index<numberOfNodes; index++)
  {
    // variables
    node *nodeTree1, *nodeTree2;

    // gets a node from arrayA
    nodeTree1 = *(arrayA + index);

    // gets a node from arrayB
    nodeTree2 = *(arrayB + index);

    // compares nodes
    if (nodeTree1->data != nodeTree2->data)
      return FALSE;
  }

  // indicates that these trees are kindred spirits
  return TRUE;
}
/*      Helper functions        */
/** Allocates new memory space for a node and assigns value.
    @param  data    data to be inserted at that node
    @return node    newly allocated memory space
 */
node* createNode (int data)
{
  // variables
  node* newNode;

  // allocates memory for the node
  newNode = malloc(sizeof(node));

  // stores data
  newNode->data = data;

  // initializes left an right subnodes
  newNode->left = newNode->right = NULL;

  // returns node
  return newNode;
}

/** Prints preorder traversal: node and its subnodes information.
    @param  root   root node to be printed
 */
void printPreOrderTraversal (node *root)
{
  // consistency: returns if there is no node
  if (root == NULL)
    return;

  // prints node information
  printf("%d ", root->data);

  // prints left subnode
  printPreOrderTraversal(root->left);

  // prints right subnode
  printPreOrderTraversal(root->right);
}

/** Prints inorder traversal: node and its subnodes information.
    @param  root   root node to be printed
 */
void printInOrderTraversal (node *root)
{
  // consistency: returns if there is no node
  if (root == NULL)
    return;

  // prints left subnode
  printInOrderTraversal(root->left);

  // prints node information
  printf("%d ", root->data);

  // prints right subnode
  printInOrderTraversal(root->right);
}

/** Prints postorder traversal: node and its subnodes information.
    @param  root   root node to be printed
 */
void printPostOrderTraversal (node *root)
{
  // consistency: returns if there is no node
  if (root == NULL)
    return;

  // prints left subnode
  printPostOrderTraversal(root->left);

  // prints right subnode
  printPostOrderTraversal(root->right);

  // prints node information
  printf("%d ", root->data);
}

/** Prints node and its subnodes information.
    @param  root   root node to be printed
 */
void printNodes(node *root)
{
  // consistency: returns if there is no node
  if (root == NULL)
    return;

  // prints node information
  printf("node: %d", root->data);

  // prints left subnode information
  if (root->left != NULL)
    printf(", left: %d", root->left->data);

  // prints right subnode information
  if (root->right != NULL)
    printf(", right: %d", root->right->data);
  printf("\n");

  // prints left subnode
  printNodes(root->left);

  // prints right subnode
  printNodes(root->right);
}

/** Checks if two tree nodes are equal.
    @param  a    node for comparison
    @param  b    node for comparison
    @return int      if the nodes are equal, returns true; otherwise, returns false
 */
int isEqual (node *a, node *b)
{
  // consistency: checks if both nodes are null
  if ((a == NULL) && (b == NULL))
  {
    // returns true: both nodes are null
    return TRUE;
  }

  // consistency: checks if only one node is null
  if ((a == NULL) || (b == NULL))
  {
    // returns false: the nodes are not equal
    return FALSE;
  }

  // compares datas
  if ((a->data) != (b->data))
    return FALSE;

  // recursively compares the subnodes
  return ((isEqual(a->left, b->left)) && (isEqual(a->right, b->right)));
}

/** Counts the number of nodes.
    @param  root   root node of the tree
    @return int    number of nodes
 */
int countNodes (node *root)
{
  int numberOfNodes = 0;

  // consistency: returns if there is no node
  if (root == NULL)
    return 0;

  // increments the counter
  numberOfNodes++;

  // adds the left subnode
  numberOfNodes += countNodes(root->left);

  // adds the right subnode
  numberOfNodes += countNodes(root->right);

  // returns the number of nodes
  return numberOfNodes;
}

/** Gets the nodes in preorder traversal from a tree to an array.
    @param  root   origin: root node of the tree
    @param  array  destiny: array to store the addresses of the nodes
 */
void getPreOrderNodes (node *root, node* *array)
{
  // variables
  static node* *arrayOfNodes;

  // consistency: returns if there is no node
  if (root == NULL)
    return;

  // uses static variable to avoid problems with the recursion
  arrayOfNodes = array;

  // stores the address of the node in the array
  *arrayOfNodes = root;

  // increments the position for the next element
  arrayOfNodes++;

  // follows the left subnode
  getPreOrderNodes(root->left, arrayOfNodes);

  // follows right subnode
  getPreOrderNodes(root->right, arrayOfNodes);
}

/** Gets the nodes in postorder traversal from a tree to an array.
    @param  root   origin: root node of the tree
    @param  array  destiny: array to store the addresses of the nodes
 */
void getPostOrderNodes (node *root, node* *array)
{
  // variables
  static node* *arrayOfNodes;

  // consistency: returns if there is no node
  if (root == NULL)
    return;

  // uses static variable to avoid problems with the recursion
  arrayOfNodes = array;

  // follows the left subnode
  getPostOrderNodes(root->left, arrayOfNodes);

  // follows right subnode
  getPostOrderNodes(root->right, arrayOfNodes);

  // stores the address of the node in the array
  *arrayOfNodes = root;

  // increments the position for the next element
  arrayOfNodes++;
}
/*      Feedback functions      */
/** difficultyRating
    @return  double   difficult rating
*/
double difficultyRating(void)
{
    return 4.5;
}

/** hoursSpent
    @return  double   hours spent
*/
double hoursSpent(void)
{
    return 5.0;
}
