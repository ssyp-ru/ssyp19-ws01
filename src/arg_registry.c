#include <stdio.h>
#include "string_t.h"
#include "list.h"
#include "arg_registry.h"
#include "cli.h"

void cli_register_command(cli_module_t *cli_module){

    register_command(cli_module, CHECKOUT, "checkout", "");
    add_named_argument(cli_module, CHECKOUT, "write", "w", "", 0);
    add_positional_argument(cli_module, CHECKOUT, "filepath", 1, "");
    add_named_argument(cli_module, CHECKOUT, "print", "p", "", 1);
    add_positional_argument(cli_module, CHECKOUT, "hello", 2, "");
    add_named_argument(cli_module, CHECKOUT, "gg", "g", "", 1);
    add_positional_argument(cli_module, CHECKOUT, "file", 3, "");
    add_named_argument(cli_module, CHECKOUT, "get", "g", "", 1);
    add_positional_argument(cli_module, CHECKOUT, "bad", 4, "");
}
