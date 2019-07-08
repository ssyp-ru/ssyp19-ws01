#ifndef INDEX_H_
#define INDEX_H_
#include "object.h"

char* get_index_path();

enum obj_return_code update_index(char *path);

void ls_files();

enum obj_return_code write_tree();

#endif
