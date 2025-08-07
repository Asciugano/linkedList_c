#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./lib/linkedList.h"

int main(void) {

  List *list = init_list(TYPE_INT);

  print_list(list);
  push(list, init_item(list, 2), 0);
  print_list(list);

  push(list, init_item(list, 43), 1);
  print_list(list);

  size_t idx = get_index(list, get_item_from_value(list, 2));
  printf("%zu\n", idx);
  print_item(list, get_item(list, idx));

  print_list(list);

  free_list(list, true);
  return 0;
}
