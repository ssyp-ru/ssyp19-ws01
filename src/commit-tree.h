#ifndef COMMIT_TREE_H_
#define COMMIT_TREE_H_
#include "string_t.h"

void commit_tree(char *parent, char *sha, char *com_mes);

void add_word(char *word, string_t *file_contents);
#endif
