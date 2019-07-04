#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "string_t.h"

struct flag;

typedef struct node {
    struct flag *value;
    struct node *prev, *next;
  } node_t;

node_t *flag_node_insert(node_t *head, struct flag *value, node_t *pos);

node_t *flag_node_find(node_t *head, struct flag *value);

node_t *flag_node_erase(node_t *head, node_t *node);

void flag_node_destroy(node_t *node);
#endif
