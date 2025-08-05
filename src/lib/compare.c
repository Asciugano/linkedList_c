#include "./compare.h"
#include <stdio.h>
#include <stdlib.h>

bool compare_int(void *a, void *b) { return (int *)a == (int *)b; }

void int_toString(void *data, char *buffer) {
  sprintf(buffer, "%d", *(int *)data);
}

void free_int(void *data) { free(data); }
