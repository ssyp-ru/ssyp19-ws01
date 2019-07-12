#ifndef COMMIT_TREE_H_
#define COMMIT_TREE_H_
#include "string_t.h"
#include "cli.h"
#include "object.h"

char* get_parent(char *sha, char *str_for_parent);

char* get_env_or_default(const char* env_name, char* def_value);

void commit_tree(cli_module_t * cli_module);
void commit_tree_impl(char tree_sha[SHA_STRING_LENGTH], 
                      char parent[SHA_STRING_LENGTH], 
                      char* message,
                      char* new_sha);

#endif
