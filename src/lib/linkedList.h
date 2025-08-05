#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListItem {
  int value;
  struct ListItem *next;
} ListItem;

typedef struct {
  size_t len;
  ListItem *entry;
  ListItem *end;
} List;

List *init_list();
ListItem *init_item(int value);

ListItem *pop(List *list, int value);
size_t push(List *list, ListItem *newItem, size_t i);
void free_list(List *list, bool clean_struct);
char *get_string_to_print(List *list);
void print_list(List *list);
