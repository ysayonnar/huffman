#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../hashtable/hashtable.h"
#include "../tree/tree.h"
#include "stdio.h"

#define MAX_FILENAME_LENGTH 100
#define SIGNATURE "HUFF"

void Decode(char *inputFilename, char *outputFilename);
void Encode(char *inputFilename, char *outputFilename);

HashTable *calculateFrequency(FILE *file);
TreeNode *createHuffmanTree(HashTable *ht);
HashTableArray *createHuffmanCodes(TreeNode *huffmanTree,
                                   HashTable *frequencyTable);
void writeHeader(HashTableArray *codes, TreeNode *huffmanTree, FILE *inputFile,
                 FILE *outputFile);
int checkSignature(FILE *inputFile);
void writeEncoded(FILE *sourceFile, FILE *outputFile, HashTableArray *codes);
float calculateCompression(char *inputFilename, char *outputFilename);

void clearBuffer();
int strLength(char *str);
int inputNumber(char *message, int min, int max);

#endif
