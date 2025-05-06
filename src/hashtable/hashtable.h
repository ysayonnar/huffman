#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../slice/slice.h"

#define MAX_TABLE_SIZE 256

typedef struct {
  int isFilled;
  int value;
} HashEntry;

typedef struct {
  HashEntry table[MAX_TABLE_SIZE];
} HashTable;

// хеш-таблица где значение - массив, для создания таблици Хаффмана
typedef struct {
  int isFilled;
  Slice *slice;
} HashEntryArray;

typedef struct {
  HashEntryArray table[MAX_TABLE_SIZE];
} HashTableArray;

void initTable(HashTable *ht);
void insertTable(HashTable *ht, char key, int value);
int getTable(HashTable *ht, char key, int *result);
void removeTable(HashTable *ht, char key);

void initTableArray(HashTableArray *ht);
void insertTableArray(HashTableArray *ht, char key, Slice *slice);
int getTableArray(HashTableArray *ht, char key, Slice **slice);
void removeTableArray(HashTableArray *ht, char key);

#endif
