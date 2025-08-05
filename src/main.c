#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./lib/linkedList.h"

int main(void) {

  List *list = init_list();

  print_list(list);

  push(list, init_item(9), 0);
  print_list(list);

  push(list, init_item(12), 0);
  print_list(list);

  pop(list, 9);
  print_list(list);

  free_list(list, true);

  return 0;
}
