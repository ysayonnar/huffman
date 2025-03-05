#include "stdio.h"
#include "stdlib.h"
#include "src/hashtable/hashtable.h"

int main(){
	FILE *file = fopen("text.txt", "r");

	if(file == NULL){
		perror("Error while file opening");
		return 1;
	}

	HashTable ht;
	initTable(&ht);

	int ch;
	while((ch = fgetc(file)) != EOF){
		int freq = 0;
		getTable(&ht, ch, &freq);
		insertTable(&ht, ch, freq+1);
	}

	for (int i = 0; i < 256; i++) {
		int freq;
		int isFound = getTable(&ht, i, &freq);
		if (!isFound){
			continue;
		}

		printf("%c: %d\n", i, freq);
	}

	fclose(file);
}