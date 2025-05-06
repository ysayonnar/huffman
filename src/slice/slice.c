#include "slice.h"
#include "stdio.h"
#include "stdlib.h"

Slice *newSlice() {
  Slice *slice = (Slice *)malloc(sizeof(Slice));

  slice->values = NULL;
  slice->capacity = 0;
  slice->len = 0;

  return slice;
}

void append(Slice *slice, int value) {
  if (slice->capacity == 0) {
    slice->capacity = 1;
    slice->len = 1;
    slice->values = (int *)malloc(sizeof(int));
  } else {
    if (slice->len == slice->capacity) {
      slice->capacity *= 2;
      slice->values =
          (int *)realloc(slice->values, sizeof(int) * slice->capacity);
    }
    slice->len++;
  }

  *(slice->values + slice->len - 1) = value;
}

void printSlice(Slice *slice) {
  if (slice->len == 0) {
    printf("Slice is empty\n");
  }

  for (int i = 0; i < slice->len; i++) {
    printf("%d ", *(slice->values + i));
  }

  printf("\n");
}

void freeSlice(Slice *slice) {
  free(slice->values);
  slice->len = 0;
  slice->capacity = 0;
}
