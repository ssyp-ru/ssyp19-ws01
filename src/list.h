#ifndef LIST_H_
#define LIST_H_
// Review: do you need this?
#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "string_t.h"

struct argument;

//! Review: flag_list_t
typedef struct flag_list {
    struct argument *value;
    struct flag_list *prev, *next;
  } flag_list_t;

flag_list_t *flag_list_insert(flag_list_t *head, struct argument *value, flag_list_t *pos);

flag_list_t *flag_list_find(flag_list_t *head, struct argument *value);

flag_list_t *flag_list_erase(flag_list_t *head, flag_list_t *node);

void flag_list_destroy(flag_list_t *node);
#endif
