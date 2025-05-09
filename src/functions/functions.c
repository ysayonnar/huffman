#include "functions.h"
#include "../priority-queue/priority-queue.h"
#include "stdint.h"
#include "stdlib.h"
#include <stdio.h>

TreeNode *buildHuffmanTree(FILE *in) {
  int marker = fgetc(in);
  if (marker == EOF) {
    return NULL;
  }

  if (marker == '1') {
    int symbol = fgetc(in);
    if (symbol == EOF) {
      return NULL;
    }

    return newTreeNode(symbol);

  } else if (marker == '0') {
    TreeNode *left = buildHuffmanTree(in);
    TreeNode *right = buildHuffmanTree(in);
    if (!left || !right) {
      return NULL;
    }

    TreeNode *node = newTreeNode(-1);
    node->left = left;
    node->right = right;
    return node;
  } else {
    fprintf(stderr, "Invalid tree marker: %c\n", marker);
    return NULL;
  }
}

void Decode(char *inputFilename, char *outputFilename) {
  FILE *inputFile = fopen(inputFilename, "rb");
  if (inputFile == NULL) {
    perror("File does not exists!!!");
    return;
  }

  int paddingbits;
  fread(&paddingbits, sizeof(int), 1, inputFile);

  TreeNode *huffmanTree = buildHuffmanTree(inputFile);

  FILE *outputFile = fopen(outputFilename, "w");
  if (outputFile == NULL) {
    perror("Error while creating output file");
    return;
  }

  TreeNode *current = huffmanTree;
  uint8_t byte;
  int bit_counter = 0;
  while (fread(&byte, 1, 1, inputFile) == 1) {
    for (int i = 7; i >= 0; i--) {
      int bit = (byte >> i) & 1;
      if (bit == 0) {
        current = current->left;
      } else {
        current = current->right;
      }

      if (current == NULL) {
        i = -1;
        continue;
      }

      if (current->value != -1) {
        fputc(current->value, outputFile);
        current = huffmanTree;
      }
    }
  }

  fclose(inputFile);
  fclose(outputFile);
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

  writeHeader(huffmanCodes, huffmanTree, inputFile, outputFile);
  rewind(inputFile); // return pointer to the beginning of file

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

int calculatePaddingBits(FILE *sourceFile, HashTableArray *codes) {
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
        bytesBuffer = 0;
        bitcount = 0;
      }
    }
  }

  if (bitcount != 0) {
    return 8 - bitcount;
  }

  return 0;
}

void writeHuffmanTree(FILE *outputFile, TreeNode *node) {
  if (node == NULL) {
    return;
  }

  if (node->left == NULL && node->right == NULL) {
    fputc('1', outputFile);
    fputc(node->value, outputFile);
  } else {
    fputc('0', outputFile);
    writeHuffmanTree(outputFile, node->left);
    writeHuffmanTree(outputFile, node->right);
  }
}

void writeHeader(HashTableArray *codes, TreeNode *huffmanTree, FILE *inputFile,
                 FILE *outputFile) {
  int paddingbits = calculatePaddingBits(inputFile, codes);
  fwrite(&paddingbits, sizeof(int), 1, outputFile);

  writeHuffmanTree(outputFile, huffmanTree);
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

  if (bitcount != 0) {
    bytesBuffer = bytesBuffer << (8 - bitcount);
    fwrite(&bytesBuffer, sizeof(uint8_t), 1, outputFile);
  }
}
