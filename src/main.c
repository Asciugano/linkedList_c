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

  printf("%zu\n", get_index(list, get_item_from_value(list, 's')));

  free_list(list, true);
  return 0;
}
