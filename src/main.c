#include "cli.h"
#include "list.h"
#include "index.h"


int main(int argc, char *argv[]){
    cli_module_t *cli_module = cli_create();
    cli_register_command(cli_module);
    cli_parse(cli_module, argc, argv);
    switch (cli_module->num_command){
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
    }
    return 0;
}
