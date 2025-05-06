#include "priority-queue.h"
#include <stdlib.h>

QueueNode *newQueueNode(TreeNode *value, int priority) {
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));

  node->value = value;
  node->priority = priority;
  node->next = NULL;

  return node;
}

void insertQueue(QueueNode **queue, TreeNode *value, int priority) {
  QueueNode *newNode = newQueueNode(value, priority);

  if (*queue == NULL) {
    *queue = newNode;
    return;
  }

  QueueNode *prev = NULL;
  QueueNode *current = *queue;
  while (current != NULL) {
    if (current->priority > priority) {
      if (prev == NULL) {
        *queue = newNode;
        newNode->next = current;
      } else {
        prev->next = newNode;
        newNode->next = current;
      }
      return;
    }
    prev = current;
    current = current->next;
  }

  prev->next = newNode;
}

QueueNode *popQueue(QueueNode **queue) {
  if (*queue == NULL) {
    return NULL;
  }

  QueueNode *poppedNode = *queue;
  *queue = poppedNode->next;

  return poppedNode;
}
