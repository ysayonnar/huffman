#include "hashtable.h"
#include <stdlib.h>

#define MAX_TABLE_SIZE 256

void initTable(HashTable *ht) {
  for (int i = 0; i < MAX_TABLE_SIZE; i++) {
    ht->table[i].isFilled = 0;
  }
}

void insertTable(HashTable *ht, char key, int value) {
  int idx = (unsigned char)key;
  ht->table[idx].isFilled = 1;
  ht->table[idx].value = value;
}

int getTable(HashTable *ht, char key, int *result) {
  int idx = (unsigned char)key;
  if (ht->table[idx].isFilled) {
    *result = ht->table[idx].value;
    return 1;
  }
  return 0;
}

void removeTable(HashTable *ht, char key) {
  int idx = (unsigned char)key;
  ht->table[idx].isFilled = 0;
}

void initTableArray(HashTableArray *ht) {
  for (int i = 0; i < MAX_TABLE_SIZE; i++) {
    ht->table[i].isFilled = 0;
  }
}

void insertTableArray(HashTableArray *ht, char key, Slice *slice) {
  int idx = (unsigned char)key;
  ht->table[idx].isFilled = 1;
  ht->table[idx].slice = slice;
}

int getTableArray(HashTableArray *ht, char key, Slice **slice) {
  int idx = (unsigned char)key;
  if (ht->table[idx].isFilled) {
    *slice = ht->table[idx].slice;
    return 1;
  }
  return 0;
}

void removeTableArray(HashTableArray *ht, char key) {
  int idx = (unsigned char)key;
  ht->table[idx].isFilled = 0;
  freeSlice(ht->table[idx].slice);
}
