#include "./linkedList.h"
#include "./utils/char.h"
#include "./utils/float.h"
#include <stdlib.h>

ListItem *pop(List *list, ...) {
  if (!list)
    return NULL;

  ListItem *head = list->entry;
  if (!head)
    return NULL;

  va_list args;
  va_start(args, list);
  void *value = list->make(args);
  va_end(args);

  if (!value)
    return NULL;

  if (list->cmp(head->value, value)) {
    ListItem *next = head->next;
    if (list->free)
      list->free(head->value);
    free(head);
    list->entry = next;
    list->len--;

    free(value);
    return next;
  }

  ListItem *prev = head;
  ListItem *curr = head->next;

  while (curr) {
    if (list->cmp(curr->value, value)) {
      prev->next = curr->next;
      list->len--;

      if (list->free)
        list->free(curr->value);
      free(curr);
      return head;
    }

    prev = curr;
    curr = curr->next;
  }

  free(value);
  return head;
}

size_t push(List *list, ListItem *newItem, size_t idx) {
  if (!list || !newItem)
    return (size_t)-1;

  if (idx == 0 || !list->entry) {
    if (list->entry && list->len > 0)
      newItem->next = list->entry;
    list->entry = newItem;

    if (list->len == 0)
      list->end = newItem;
    list->len++;
    return 0;
  }

  ListItem *prev = list->entry;
  size_t i = 0;
  while (prev->next && i < idx) {
    prev = prev->next;
    i++;
  }

  newItem->next = prev->next;
  prev->next = newItem;

  if (!newItem->next)
    list->end = newItem;

  list->len++;
  return i;
}

char *get_string_to_print(List *list) {
  if (!list || list->len == 0 || !list->entry) {
    char *empty = malloc(6);

    if (!empty)
      return NULL;

    strcpy(empty, "[ ]\n");
    return empty;
  }

  char *result = malloc(sizeof(char) * 1024);
  if (!result)
    return NULL;

  result[0] = '\0';
  strcat(result, "[");

  ListItem *current = list->entry;

  while (current) {
    char buffer[16];
    list->to_string(current->value, buffer);
    strcat(result, " ");
    strcat(result, buffer);
    if (current->next)
      strcat(result, ",");

    current = current->next;
  }

  strcat(result, " ]\n");
  return result;
}

void print_item(List *list, ListItem *item) {
  if (!list || !item)
    return;

  char buffer[32];
  list->to_string(item->value, buffer);
  printf("%s\n", buffer);
}

void print_list(List *list) {
  char *str = get_string_to_print(list);
  printf("%s", str);
  free(str);
}

void free_list(List *list, bool clean_struct) {
  if (!list)
    exit(1);

  ListItem *curr = list->entry;
  while (curr) {
    ListItem *next = curr->next;
    if (list->free)
      list->free(curr->value);
    free(curr);
    curr = next;
  }
  list->entry = NULL;
  list->len = 0;

  if (clean_struct)
    free(list);
}

List *init_list(DataType type) {
  List *list = malloc(sizeof(List));
  if (!list)
    return NULL;

  list->entry = NULL;
  list->end = NULL;
  list->len = 0;
  list->type = type;

  switch (type) {
  case TYPE_INT:
    list->cmp = compare_int;
    list->to_string = int_toString;
    list->free = free_int;
    list->make = (void *(*)(va_list))make_int;
    break;
  case TYPE_FLOAT:
    list->cmp = compare_float;
    list->to_string = float_toString;
    list->free = free_float;
    list->make = (void *(*)(va_list))make_float;
    break;
  case TYPE_CHAR:
    list->cmp = compare_char;
    list->to_string = char_toString;
    list->free = free_char;
    list->make = (void *(*)(va_list))make_char;
    break;
  default:
    list->cmp = NULL;
    list->to_string = NULL;
    list->free = NULL;
    break;
  }

  return list;
}

void *make_value(List *list, ...) {
  va_list args;
  va_start(args, list);
  void *result = list->make(args);
  va_end(args);

  return result;
}

ListItem *init_item(List *list, ...) {
  if (!list || !list->make)
    return NULL;

  va_list args;
  va_start(args, list);
  void *value = list->make(args);
  va_end(args);

  if (!value)
    return NULL;

  ListItem *item = calloc(1, sizeof(ListItem));
  if (!item)
    return NULL;

  item->value = value;
  item->next = NULL;

  return item;
}

size_t get_index(List *list, ListItem *item) {
  if (!list || !item)
    return (size_t)-1;

  ListItem *next = list->entry;
  size_t i = 0;
  while (next) {
    if (list->cmp(next->value, item->value))
      return i;

    next = next->next;
    i++;
  }

  return (size_t)-1;
}

ListItem *get_item(List *list, size_t idx) {
  if (!list || idx > list->len)
    return NULL;

  ListItem *next = list->entry;
  size_t count = 0;
  while (next && count != idx) {
    next = next->next;
    count++;
  }

  return next;
}

ListItem *get_item_from_value(List *list, ...) {
  if (!list || !list->make || !list->entry)
    return NULL;

  va_list args;
  va_start(args, list);
  void *value = list->make(args);
  va_end(args);

  if (!value)
    return NULL;

  ListItem *curr = list->entry;
  while (curr) {
    if (list->cmp(curr->value, value)) {
      if (list->free)
        list->free(value);
      return curr;
    }

    curr = curr->next;
  }

  if (list->free)
    list->free(value);
  return NULL;
}
