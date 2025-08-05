#include "./linkedList.h"
#include "compare.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListItem *pop(List *list, void *value, bool (*cmp)(void *, void *)) {
  ListItem *head = list->entry;
  if (!head)
    return NULL;

  if (cmp(head->value, value)) {
    ListItem *next = head->next;
    free(head);
    list->len--;
    return next;
  }

  ListItem *prev = head;
  ListItem *curr = head->next;

  while (curr) {
    if (cmp(curr->value, value)) {
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
    if (count == i) {
      prev->next = newItem;
      newItem->next = curr;
      curr->next = next;

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

char *get_string_to_print(List *list, void (*to_string)(void *, char *)) {
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
    to_string(current->value, buffer);
    strcat(result, " ");
    strcat(result, buffer);
    if (current->next)
      strcat(result, ",");

    current = current->next;
  }

  strcat(result, " ]\n");
  return result;
}

void print_list(List *list, void (*to_string)(void *, char *)) {
  char *str = get_string_to_print(list, to_string);
  printf("%s", str);
  free(str);
}

void free_list(List *list, bool clean_struct, void (*free_value)(void *)) {
  if (!list)
    exit(1);

  ListItem *curr = list->entry;
  while (curr) {
    ListItem *next = curr->next;
    if (free_value)
      free_value(curr->value);
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
    break;
  case TYPE_FLOAT:
    break;
  case TYPE_CHAR:
    break;
  deafult:
    list->cmp = NULL;
    list->to_string = NULL;
    list->free = NULL;
  }

  return list;
}

ListItem *init_item(void *value) {
  ListItem *item = malloc(sizeof(ListItem));
  if (!item)
    return NULL;

  item->value = value;
  item->next = NULL;

  return item;
}
