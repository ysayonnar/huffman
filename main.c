#include "src/functions/functions.h"
#include "src/utils/utils.h"
#include <stdio.h>

int main() {
  int option = -1;

  while (option != 0) {
    printf("\n~~~~~HUFFMAN ARCHIVER~~~~~\n");
    printf("OPTIONS:\n\t1 - archive file\n\t2 - unarchive file\n\t0 - quit\n");
    int option = inputNumber("Option: ", 0, 2);

    if (option == 0) {
      break;
    }

    char inputFileName[100];
    printf("Enter source filename: ");
    scanf("%s", inputFileName);

    char outputFileName[100];
    printf("Enter output filename: ");
    scanf("%s", outputFileName);

    if (option == 1) {
      Encode(inputFileName, outputFileName);
    } else if (option == 2) {
      Decode(inputFileName, outputFileName);
    }
  }
}
