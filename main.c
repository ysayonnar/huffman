#include "src/hashtable/hashtable.h"
#include "src/priority-queue/priority-queue.h"
#include "src/tree/tree.h"
#include "stdio.h"
#include "stdlib.h"

#define PATH_TO_FILE "./huffman-tester/data.txt"

int main() {
  FILE *file = fopen(PATH_TO_FILE, "r");

  if (file == NULL) {
    perror("Error while opening file");
    return 1;
  }

  HashTable ht;
  initTable(&ht);

  int ch;
  while ((ch = fgetc(file)) != EOF) {
    int freq = 0;
    getTable(&ht, ch, &freq);
    insertTable(&ht, ch, freq + 1);
  }

  fclose(file);

  QueueNode *queue = NULL;

  for (int i = 0; i < 256; i++) {
    int freq;
    int isFound = getTable(&ht, i, &freq);
    if (!isFound) {
      continue;
    }

    TreeNode *node = newTreeNode(i);
    insertQueue(&queue, node, freq);
  }

  while (queue->next != NULL) {
    QueueNode *first = popQueue(&queue);
    QueueNode *second = popQueue(&queue);

    TreeNode *node = newTreeNode(-1);

    node->left = first->value;
    node->right = second->value;

    insertQueue(&queue, node, first->priority + second->priority);
  }
}
