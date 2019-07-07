#include <stdio.h>
#include "string_t.h"
#include "list.h"
#include "cli.h"

void cli_register_command(cli_module_t *cli_module){ 
    register_command(cli_module, UPDATE_INDEX, "update-index", "add file to index");
    //add_named_argument(cli_module, HASH_OBJECT, "write", "w", "", 0);
    add_positional_argument(cli_module, UPDATE_INDEX, "filepath", 1, "path to file");

    register_command(cli_module, LS_FILES, "ls-files", "list of indexed files");

    register_command(cli_module, WRITE_TREE, "write-tree", "add tree to index");

    register_command(cli_module, CAT_FILE, "cat-file", "print gg object");
    add_positional_argument(cli_module, CAT_FILE, "sha", 1, "sha");

    register_command(cli_module, HASH_OBJ, "hash-object", "create gg object");
    add_positional_argument(cli_module, HASH_OBJ, "filepath", 1, "path to file");
}
