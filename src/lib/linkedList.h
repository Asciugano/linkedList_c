#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_va_list.h>

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
  void *(*make)(va_list);
} List;

void *make_value(List *list, ...);

List *init_list(DataType type);
ListItem *init_item(List *list, ...);
void free_list(List *list, bool clean_struct);

size_t get_index(List *list, ListItem *item);
ListItem *get_item(List *list, size_t idx);
ListItem *pop(List *list, void *value);
size_t push(List *list, ListItem *newItem, size_t i);
char *get_string_to_print(List *list);
void print_list(List *list);
