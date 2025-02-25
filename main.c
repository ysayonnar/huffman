#include "stdio.h"
#include "stdlib.h"
#include "src/hashtable/hashtable.h"
#include "src/utils/utils.h"

int main(){
	char *str = (char*)malloc(sizeof(char) * 100);
	HashTable ht;
	initTable(&ht);

	scanf("%20s", str);
	
	for (int i = 0; i < strLength(str); i++) {
		int currentFrequency = 0;
		getTable(&ht, str[i], &currentFrequency);
		insertTable(&ht, str[i], currentFrequency+1);

		printf("%c: %d\n", str[i], str[i]);
	}

	printf("\n\n");

	for (int i = 0; i < 256; i++) {
		int frequency = -1;
		getTable(&ht, i, &frequency);

		if(frequency != -1){
			printf("Symbol: %c, ASCII: %d, frequency: %d\n", i, i, frequency);
		}
	}
}