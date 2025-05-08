#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../hashtable/hashtable.h"
#include "../tree/tree.h"
#include "stdio.h"

#define MAX_FILENAME_LENGTH 100

void Decode(char *inputFilename, char *outputFilename);
void Encode(char *inputFilename, char *outputFilename);

HashTable *calculateFrequency(FILE *file);
TreeNode *createHuffmanTree(HashTable *ht);
HashTableArray *createHuffmanCodes(TreeNode *huffmanTree,
                                   HashTable *frequencyTable);
void writeHeader(HashTableArray *codes, FILE *inputFile, FILE *outputFile);
void writeEncoded(FILE *sourceFile, FILE *outputFile, HashTableArray *codes);

#endif
