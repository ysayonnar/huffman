#include "src/functions/functions.h"
#include "src/utils/utils.h"
#include <stdio.h>

int main() {
  printf("Choose option:\n\t1 - archive\n\t2 - unarchive\n");
  int option = inputNumber("Option: ", 1, 2);

  char inputFileName[100];
  printf("Enter input filename: ");
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
