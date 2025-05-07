#include "functions.h"
#include "../priority-queue/priority-queue.h"
#include "stdint.h"
#include "stdlib.h"

void Decode(char *inputFilename, char *outputFilename) {
  // TODO: implement
}

void Encode(char *inputFilename, char *outputFilename) {
  FILE *inputFile = fopen(inputFilename, "r");
  if (inputFile == NULL) {
    perror("File does not exists!!!");
    return;
  }

  HashTable *frequencyTable = calculateFrequency(inputFile);
  fclose(inputFile);

  TreeNode *huffmanTree = createHuffmanTree(frequencyTable);

  HashTableArray *huffmanCodes =
      createHuffmanCodes(huffmanTree, frequencyTable);

  inputFile = fopen(inputFilename, "r");
  if (inputFile == NULL) {
    perror("File does not exists!!!");
    return;
  }
  rewind(inputFile);

  FILE *outputFile = fopen(outputFilename, "wb");
  if (outputFile == NULL) {
    perror("Error while opening file");
    return;
  }

  writeEncoded(inputFile, outputFile, huffmanCodes);

  fclose(inputFile);
  fclose(outputFile);
}

HashTable *calculateFrequency(FILE *file) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  initTable(ht);

  int ch;
  while ((ch = fgetc(file)) != EOF) {
    int freq = 0;
    getTable(ht, ch, &freq);
    insertTable(ht, ch, freq + 1);
  }

  return ht;
}

TreeNode *createHuffmanTree(HashTable *ht) {
  QueueNode *queue = NULL;
  for (int i = 0; i < 256; i++) {
    int freq;
    int isFound = getTable(ht, i, &freq);
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

  return queue->value;
}

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

HashTableArray *createHuffmanCodes(TreeNode *huffmanTree,
                                   HashTable *frequencyTable) {
  HashTableArray *codesTable = (HashTableArray *)malloc(sizeof(HashTableArray));
  initTableArray(codesTable);

  for (int i = 0; i < 256; i++) {
    int freq;
    int isFound = getTable(frequencyTable, i, &freq);
    if (!isFound) {
      continue;
    }

    Slice *slice = newSlice();
    createCode(huffmanTree, slice, i);
    insertTableArray(codesTable, i, slice);
  }

  return codesTable;
}

void writeEncoded(FILE *sourceFile, FILE *outputFile, HashTableArray *codes) {
  uint8_t bytesBuffer = 0;
  int bitcount = 0;
  int symbol;
  while ((symbol = fgetc(sourceFile)) != EOF) {
    Slice *slice;
    int isFound = getTableArray(codes, symbol, &slice);
    if (!isFound) {
      continue;
    }

    for (int i = slice->len - 1; i >= 0; i--) {
      int bit = *(slice->values + i);
      bytesBuffer = (bytesBuffer << 1) | (bit & 1);
      bitcount++;

      if (bitcount == 8) {
        fwrite(&bytesBuffer, sizeof(uint8_t), 1, outputFile);
        bytesBuffer = 0;
        bitcount = 0;
      }
    }
  }
  // TODO: padding bits issue
}
