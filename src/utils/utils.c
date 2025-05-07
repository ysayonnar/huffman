#include "utils.h"
#include "stdio.h"

int strLength(char *str) {
  int length = 0;
  while (*(str + length) != '\0') {
    length++;
  }
  return length;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
