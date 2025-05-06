#ifndef SLICE_H
#define SLICE_H

typedef struct {
  int *values;
  int len;
  int capacity;
} Slice;

Slice *newSlice();

void append(Slice *slice, int value);

void printSlice(Slice *slice);

void freeSlice(Slice *slice);

#endif
