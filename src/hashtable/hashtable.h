#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_TABLE_SIZE 256

typedef struct {
    int isFilled; // флаг наличия элемента
    int value;
} HashEntry;

typedef struct {
    HashEntry table[MAX_TABLE_SIZE];
} HashTable;

void initTable(HashTable *ht);
void insertTable(HashTable *ht, char key, int value);
int getTable(HashTable *ht, char key, int *result);
void removeTable(HashTable *ht, char key);

#endif // HASHTABLE_H