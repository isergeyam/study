#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#define TRUE 1
#define FALSE 0

/* a link in the queue, holds the info and point to the next Node*/
typedef struct
{
  intptr_t info;
} DATA;

typedef struct Node_t
{
  DATA data;
  struct Node_t *prev;
} NODE;

/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct Queue
{
  NODE *head;
  NODE *tail;
  int size;
  int limit;
} Queue;

Queue *ConstructQueue(int limit);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue *pQueue);

Queue *ConstructQueue(int limit)
{
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  if (queue == NULL)
  {
    return NULL;
  }
  if (limit <= 0)
  {
    limit = 65535;
  }
  queue->limit = limit;
  queue->size = 0;
  queue->head = NULL;
  queue->tail = NULL;

  return queue;
}

void DestructQueue(Queue *queue)
{
  NODE *pN;
  while (!isEmpty(queue))
  {
    pN = Dequeue(queue);
    free(pN);
  }
  free(queue);
}

int Enqueue(Queue *pQueue, NODE *item)
{
  /* Bad parameter */
  if ((pQueue == NULL) || (item == NULL))
  {
    return FALSE;
  }
  // if(pQueue->limit != 0)
  if (pQueue->size >= pQueue->limit)
  {
    return FALSE;
  }
  /*the queue is empty*/
  item->prev = NULL;
  if (pQueue->size == 0)
  {
    pQueue->head = item;
    pQueue->tail = item;
  }
  else
  {
    /*adding item to the end of the queue*/
    pQueue->tail->prev = item;
    pQueue->tail = item;
  }
  pQueue->size++;
  return TRUE;
}

NODE *Dequeue(Queue *pQueue)
{
  /*the queue is empty or bad param*/
  NODE *item;
  if (isEmpty(pQueue))
    return NULL;
  item = pQueue->head;
  pQueue->head = (pQueue->head)->prev;
  pQueue->size--;
  return item;
}

int isEmpty(Queue *pQueue)
{
  if (pQueue == NULL)
  {
    return FALSE;
  }
  if (pQueue->size == 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

typedef struct node Node;

struct node
{
  int value;
  Node *left;
  Node *right;
};

Node *insert(Node *root, int v)
{
  if (root == NULL)
  {
    root = malloc(sizeof(Node));
    root->value = v;
    root->left = NULL;
    root->right = NULL;
  }
  else if (v < root->value)
  {
    root->left = insert(root->left, v);
  }
  else
  {
    root->right = insert(root->right, v);
  }

  return root;
}

Node *bstMax(Node *root)
{
  if (root == NULL)
  {
    return NULL;
  }
  while (root->right != NULL)
  {
    root = root->right;
  }
  return root;
}

Node *bstMin(Node *root)
{
  if (root == NULL)
  {
    return NULL;
  }
  while (root->left != NULL)
  {
    root = root->left;
  }
  return root;
}

Node *bstSucc(Node *root, Node *node)
{
  if (node == NULL || root == NULL)
  {
    return NULL;
  }
  if (node->right != NULL)
  {
    return bstMin(node->right);
  }

  struct node *succ = NULL;

  // Start from root and search for
  // successor down the tree
  while (root != NULL)
  {
    if (node->value < root->value)
    {
      succ = root;
      root = root->left;
    }
    else if (node->value > root->value)
      root = root->right;
    else
      break;
  }

  return succ;
}

/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
Node *bstDelete(Node *root, int k)
{
  // Base case
  if (root == NULL)
    return root;

  // Recursive calls for ancestors of
  // node to be deleted
  if (root->value > k)
  {
    root->left = deleteNode(root->left, k);
    return root;
  }
  else if (root->value < k)
  {
    root->right = deleteNode(root->right, k);
    return root;
  }

  // We reach here when root is the node
  // to be deleted.

  // If one of the children is empty
  if (root->left == NULL)
  {
    Node *temp = root->right;
    free(root);
    return temp;
  }
  else if (root->right == NULL)
  {
    Node *temp = root->left;
    free(root);
    return temp;
  }
  // If both children exist
  else
  {

    Node *succParent = root;

    // Find successor
    Node *succ = root->right;
    while (succ->left != NULL)
    {
      succParent = succ;
      succ = succ->left;
    }
    // Delete successor.  Since successor
    // is always left child of its parent
    // we can safely make successor's right
    // right child as left of its parent.
    // If there is no succ, then assign
    // succ->right to succParent->right
    if (succParent != root)
      succParent->left = succ->right;
    else
      succParent->right = succ->right;

    // Copy Successor Data to root
    root->value = succ->value;

    // Delete Successor and return root
    free(succ);
    return root;
  }
}

void dfsTraverse(Node *root)
{
  if (root == NULL)
  {
    return;
  }

  dfsTraverse(root->left);
  printf("%d,", root->value);
  dfsTraverse(root->right);
}

int bstSize(Node *root)
{
  return root == NULL ? 0 : bstSize(root->left) + bstSize(root->right) + 1;
}

void bfsTraverse(Node *root)
{
  if (root == NULL)
  {
    return;
  }

  Queue *q = ConstructQueue(bstSize(root));
  NODE *pN = (NODE *)malloc(sizeof(NODE));
  pN->data.info = (intptr_t)root;
  Enqueue(q, pN);
  while (!isEmpty(q))
  {
    NODE *to_delete = Dequeue(q);
    Node *node = (Node *)(to_delete->data.info);
    printf("%d,", node->value);

    // copypaste, don't do that :)
    pN = (NODE *)malloc(sizeof(NODE));
    pN->data.info = (intptr_t)node->left;
    Enqueue(q, pN);
    pN = (NODE *)malloc(sizeof(NODE));
    pN->data.info = (intptr_t)node->right;
    Enqueue(q, pN);

    // don't forget that
    free(to_delete);
  }
  DestructQueue(q);
}
