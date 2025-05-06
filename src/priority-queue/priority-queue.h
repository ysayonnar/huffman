#ifndef PRIOTIYQUEUE_H
#define PRIOTIYQUEUE_H

#include "../tree/tree.h"

// implementation min queue

typedef struct QueueNode {
  int priority;
  struct TreeNode *value;
  struct QueueNode *next;
} QueueNode;

QueueNode *newQueueNode(TreeNode *value, int priority);
void insertQueue(QueueNode **queue, TreeNode *value, int priority);
QueueNode *popQueue(QueueNode **queue);

#endif
