#ifndef INDEX_H_
#define INDEX_H_
// Review: do you need all this headers here? (you should have only headers you need for this file)
#include <stdio.h>
#include "string_t.h"
#include "fs.h"
#include "object.h"
#include <openssl/sha.h>

int update_index(char *path);

void ls_files();

enum save_blob_error_code write_tree();

#endif
