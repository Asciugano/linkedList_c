#include "./linkedList.h"

ListItem *pop(List *list, void *value) {
  ListItem *head = list->entry;
  if (!head)
    return NULL;

  if (list->cmp(head->value, value)) {
    ListItem *next = head->next;
    free(head);
    list->entry = next;
    list->len--;
    return next;
  }

  ListItem *prev = head;
  ListItem *curr = head->next;

  while (curr) {
    if (list->cmp(curr->value, value)) {
      prev->next = curr->next;
      free(curr);
      list->len--;
      return head;
    }

    prev = curr;
    curr = curr->next;
  }

  return head;
}

size_t push(List *list, ListItem *newItem, size_t i) {
  if (!list || !newItem)
    exit(1);
  if (i == 0 || !list->entry) {
    ListItem *next = list->entry;
    newItem->next = next ? next : NULL;
    list->entry = newItem;

    list->len++;

    if (list->len == 1) {
      list->end = newItem;
    }

    return 0;
  }

  size_t count = 0;
  ListItem *head = list->entry;
  ListItem *curr = head->next;
  ListItem *prev = head;

  while (count < list->len && curr) {
    ListItem *next = curr->next;

    if (count >= list->len - 2)
      list->end = newItem;
    if (count == i - 1) {
      prev->next = newItem;
      newItem->next = curr;

      list->len++;
      return count;
    }
    prev = curr;
    curr = curr->next;
    next = next->next;
    count++;
  }

  prev->next = newItem;
  newItem->next = NULL;
  list->len++;
  return count;
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
    break;
  case TYPE_CHAR:
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
  if (!list || idx < 0 || idx > list->len)
    return NULL;

  ListItem *next = list->entry;
  size_t count = 0;
  while (next && count != idx) {
    next = next->next;
    count++;
  }

  return next;
}
