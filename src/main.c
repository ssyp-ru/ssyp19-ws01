#include "text_diff.h"
#include <stdio.h>
#include "cli.h"
#include "list.h"
#include "index.h"
#include "commit-tree.h"
#include "checkout.h"
#include "commit.h"
#include "git_log.h"
#include "checkout.h"
#include "config.h"
#include "help.h"


int printim(diff_t **diffs, int num){
    for(int i = num - 1; i >= 0; i--){
        printf("(%d %d %d %d %d)\n", diffs[i]->s1_from, diffs[i]->s1_len, diffs[i]->s2_from, diffs[i]->s2_len, diffs[i]->diff_type );
    
}
}


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
        case COMMIT: {
            commit(cli_get_argument(cli_module, "message"));
        }
        case LOG: {
            git_log(cli_module);
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
            char sha[SHA_STRING_LENGTH];
            write_tree(sha);
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
        case ADD: {
            update_index(cli_get_argument(cli_module, "filepath"));
            break;
        }
        default: {
            fprintf(stderr, "ERROR: unknown command type");
        }
    }
    return 0;
}
