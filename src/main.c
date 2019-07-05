#include "cli.h"
#include "list.h"


int main(int argc, char *argv[]){
    cli_module_t *cli_module = cli_create();
    cli_register_command(cli_module);
    cli_parse(cli_module, argc, argv);
    switch (cli_module->num_command){
        case CHECKOUT: {
            // here call for hash_object function
            break;
        }

    }
    return 0;
}
