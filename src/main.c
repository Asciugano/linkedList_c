#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./lib/linkedList.h"

int main(void) {

  List *list = init_list(TYPE_CHAR);

  push(list, init_item(list, 's'), 0);
  print_list(list);

  push(list, init_item(list, 'a'), 0);
  print_list(list);

  printf("index of item->value = s: %zu\n",
         get_index(list, get_item_from_value(list, 's')));

  pop(list, 'a');
  print_list(list);

  push(list, init_item(list, 'h'), 1);
  push(list, init_item(list, 'c'), 2);

  size_t idx = get_index(list, get_item_from_value(list, 'c'));
  printf("index of item->value = c: %zu\n", idx);
  print_item(list, get_item(list, idx));

  print_list(list);

  free_list(list, true);
  return 0;
}
