#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./lib/linkedList.h"

int main(void) {

  List *list = init_list(TYPE_INT);

  push(list, init_item(list, 42), 0);
  print_list(list);

  push(list, init_item(list, 54), 1);
  print_list(list);

  free_list(list, true);

  return 0;
}
