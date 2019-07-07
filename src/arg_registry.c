#include <stdio.h>
#include "string_t.h"
#include "list.h"
#include "cli.h"

void cli_register_command(cli_module_t *cli_module){ 
    register_command(cli_module, HASH_OBJECT, "hash-object", "help message for hash-object");
    add_named_argument(cli_module, HASH_OBJECT, "write", "w", "", 0);
    add_positional_argument(cli_module, HASH_OBJECT, "filepath", 1, "");
}
