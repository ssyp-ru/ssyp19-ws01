#include "cli.h"
#include "list.h"
#include "index.h"
#include "commit-tree.h"
#include "checkout.h"
#include "config.h"


int main(int argc, char *argv[]){
    cli_module_t *cli_module = cli_create();
    cli_register_command(cli_module);
    config_initialize();

    if (cli_parse(cli_module, argc, argv) == 0) {
        fprintf(stderr, "Argument parse error, abort.\n");
    }
    switch (cli_module->num_command){
        case COMMIT_TREE: {
            commit_tree(cli_module);
            break;
        }
        case UPDATE_INDEX: {
            update_index(cli_get_argument(cli_module, "filepath"));
            // here call for hash_object function
            break;
        }
        case LS_FILES: {
            ls_files();
            break;
        }
        case WRITE_TREE: {
            write_tree();
            break;
        }
        case CAT_FILE: {
            cat_file(cli_get_argument(cli_module, "sha"));
            break;
        }
        case HASH_OBJ: {
            hash_object(cli_get_argument(cli_module, "filepath"));
            break;
        }
        case CHECKOUT: {
            checkout(cli_get_argument(cli_module, "sha"));
            break;
        }
        case CONFIG: {
            char* name = cli_get_argument(cli_module, "name");
            char* email = cli_get_argument(cli_module, "email");
            if (name) {
                config_set_name(name);
            }
            if (email) {
                config_set_email(email);
            }
            break;
        }
        default: {
            fprintf(stderr, "ERROR: unknown command type");
        }
    }
    return 0;
}
