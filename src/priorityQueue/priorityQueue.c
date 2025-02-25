#include "stdio.h"
#include "stdlib.h"

typedef struct Node{
	char symbol;
	int frequency;
	struct Node *left;
	struct Node *right;
} Node;

typedef struct{
	Node* values;
	int len;
}PriorityQueue;

void initPriorityQueue(PriorityQueue *ht){
	Node *nodes = (Node*)malloc(0);
	ht->values = nodes;
	ht->len = 0;
}

int less(PriorityQueue *pq, int i, int j){
	return pq->values[i].frequency < pq->values[j].frequency;
}

void swap(PriorityQueue *pq, int i, int j){
	Node temp = pq->values[i];
	pq->values[i] = pq->values[j];
	pq->values[j] = temp;
}

//TODO: дописать реализацию

