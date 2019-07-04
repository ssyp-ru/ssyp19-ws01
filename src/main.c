#include "cli.h"
#include "list.h"


int main(int argc, char *argv[]){
    cli_module_t *cli_module = cli_create();
    register_command(cli_module, CHECKOUT, "Checkout", "help1");
    add_named_argument(cli_module, CHECKOUT, "log", "lg", "help2", 1);
    add_positional_argument(cli_module, CHECKOUT, "MDK", 1, "help3");
    cli_parse(cli_module, argc, argv);
    cli_print(cli_module);
    test_parse_print(cli_module);
    return 0;
}
