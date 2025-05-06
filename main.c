#include "src/hashtable/hashtable.h"
#include "src/priority-queue/priority-queue.h"
#include "src/tree/tree.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define PATH_TO_FILE "./huffman-tester/data.txt"

int createCode(TreeNode *node, Slice *slice, int code) {
  if (node == NULL) {
    return 0;
  }

  if (node->value == code) {
    return 1;
  }

  if (createCode(node->left, slice, code)) {
    append(slice, 0);
    return 1;
  } else if (createCode(node->right, slice, code)) {
    append(slice, 1);
    return 1;
  } else {
    return 0;
  }
}

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

  HashTableArray codesTable;
  initTableArray(&codesTable);

  printf("CHAR\t\tCODE\n");
  for (int i = 0; i < 256; i++) {
    int freq;
    int isFound = getTable(&ht, i, &freq);
    if (!isFound) {
      continue;
    }

    Slice *slice = newSlice();
    createCode(queue->value, slice, i);
    insertTableArray(&codesTable, i, slice);

    printf("%3d\t\t", i);
    for (int j = slice->len - 1; j >= 0; j--) {
      printf("%d", *(slice->values + j));
    }
    printf("\n");
  }

  FILE *archivedFile = fopen("archived.huf", "wb");
  if (archivedFile == NULL) {
    perror("Error while opening file");
    return 1;
  }

  FILE *readFile = fopen(PATH_TO_FILE, "r");
  if (readFile == NULL) {
    perror("Error while opening file");
    return 1;
  }

  uint8_t bytesBuffer = 0;
  int bitcount = 0;
  int symbol;
  while ((symbol = fgetc(readFile)) != EOF) {
    Slice *slice;
    int isFound = getTableArray(&codesTable, symbol, &slice);
    if (!isFound) {
      continue;
    }

    for (int i = slice->len - 1; i >= 0; i--) {
      int bit = *(slice->values + i);
      bytesBuffer = (bytesBuffer << 1) | (bit & 1);
      bitcount++;

      if (bitcount == 8) {
        fwrite(&bytesBuffer, sizeof(uint8_t), 1, archivedFile);
        bytesBuffer = 0;
        bitcount = 0;
      }
    }
  }

  fclose(readFile);
  fclose(archivedFile);
}
