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

int inputNumber(char *message, int min, int max) {
  int n = 0;
  int scanfRes = 0;

  while (scanfRes == 0) {
    printf("%s", message);
    scanfRes = scanf("%d", &n);
    if (scanfRes == 0) {
      printf("\033[1;31m\tInvalid Input!\033[0m\n");
    } else if (n < min || n > max) {
      printf("\033[1;31m\tNumber must be from %d to %d!\033[0m\n", min, max);
      scanfRes = 0;
      n = 0;
    }
    clearBuffer();
  }

  return n;
}
