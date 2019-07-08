#include <stdio.h>
#include "commit-tree.h"
#include "object.h"
#include "index.h"
#include "fs.h"
#include "commit.h"


enum obj_return_code commit(char *message){
    char tree_sha[SHA_STRING_LENGTH];
    if (write_tree(tree_sha) != OK){
        return CANT_OPEN_FILE;
    }
    char head_path[MAX_PATH_LENGTH];
    if (get_gg_root_path(head_path) == -1){
        return CANT_GET_ROOT_FOLDER;
    }
    strcat(head_path, "/refs/heads/");
    strcat(head_path, "branch");
    char parent_sha[SHA_STRING_LENGTH];
    FILE *f = fopen(head_path, "r");
    if (f == NULL){
        return CANT_OPEN_FILE;
    }
    int len = fread(parent_sha, sizeof(char), SHA_STRING_LENGTH - 1, f);
    fclose(f);
    parent_sha[SHA_STRING_LENGTH - 1] = '\0';
    if (len != SHA_STRING_LENGTH - 1){
        commit_tree_impl(tree_sha, NULL, message);
        return OK;
    }
    commit_tree_impl(tree_sha, parent_sha, message);
    return OK;
}
