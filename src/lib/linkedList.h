#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "./compare.h"

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_CHAR,
} DataType;

typedef struct ListItem {
  void *value;
  struct ListItem *next;
} ListItem;

typedef struct {
  size_t len;
  ListItem *entry;
  ListItem *end;
  DataType type;

  bool (*cmp)(void *, void *);
  void (*to_string)(void *, char *);
  void (*free)(void *free);
} List;

List *init_list(DataType type);
ListItem *init_item(void *value);
void free_list(List *list, bool clean_struct, void (*free_value)(void *));

ListItem *pop(List *list, void *value, bool (*cmp)(void *, void *));
size_t push(List *list, ListItem *newItem, size_t i);
char *get_string_to_print(List *list, void (*to_string)(void *, char *));
void print_list(List *list, void (*to_string)(void *, char *));
