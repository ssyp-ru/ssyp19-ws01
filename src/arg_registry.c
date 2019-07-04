#include <stdio.h>
#include "string_t.h"
#include "list.h"
#include "cli.h"

void cli_register_command(cli_module_t *cli_module){ 
    register_command(cli_module, CHECKOUT, "checkout", "help message");
    add_named_argument(cli_module, CHECKOUT, "long_name", "l", "help message", 1);
    add_positional_argument(cli_module, CHECKOUT, "name", 1, "help message");

}
