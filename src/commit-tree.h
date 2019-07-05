#ifndef COMMIT_TREE_H_
#define COMMIT_TREE_H_
#include "string_t.h"
#include "cli.h"

char* get_env_or_default(const char* env_name, char* def_value);

void commit_tree(cli_module_t * cli_module);

#endif
