#include "../list.h"
#include "../string_t.h"
#include <assert.h>
#include "../cli.h"

void test_cli_register_command(cli_module_t *cli_module){

    register_command(cli_module, CHECKOUT, "checkout", "");
    add_named_argument(cli_module, CHECKOUT, "write", "w", "", 0);
    add_positional_argument(cli_module, CHECKOUT, "filepath", 1, "");
    add_named_argument(cli_module, CHECKOUT, "print", "p", "", 1);
    add_positional_argument(cli_module, CHECKOUT, "hello", 2, "");
    add_named_argument(cli_module, CHECKOUT, "gg", "g", "", 1);
    add_positional_argument(cli_module, CHECKOUT, "file", 3, "");
    add_positional_argument(cli_module, CHECKOUT, "bad", 4, "");
    add_named_argument(cli_module, CHECKOUT, "get", "g", "", 1);
    
    register_command(cli_module, PUSH, "push", "");
    add_named_argument(cli_module, PUSH, "write", "w", "", 0);
    add_positional_argument(cli_module, PUSH, "filepath", 1, "");
    add_named_argument(cli_module, PUSH, "print", "p", "", 1);
    add_positional_argument(cli_module, PUSH, "hello", 2, "");
    add_named_argument(cli_module, PUSH, "gg", "g", "", 1);
    add_positional_argument(cli_module, PUSH, "file", 3, "");
    add_named_argument(cli_module, PUSH, "get", "g", "", 1);
    add_positional_argument(cli_module, PUSH, "bad", 4, "");

}

int main(){
    {
        cli_module_t *cli_module = cli_create();
        test_cli_register_command(cli_module);
        char **array[4];
        //command not found
        char *argv[] = { "git", "asfjsdf", "--log", "iwue" };
        array[0] = argv;
        //expected value, but has gotten flag
        char *argv1[] = { "git", "checkout", "--gg", "-g" };
        array[1] = argv1;
        //flag not found
        char *argv2[] = { "git", "checkout", "-dd", "apsod" };
        array[2] = argv2;
        //all right
        char *argv3[] = { "git", "checkout", "-g", "alsdf" };
        array[3] = argv3;
        //no command
        char *argv10[] = {"git"};
        assert(!cli_parse(cli_module, 1, argv10));
        for (int i = 0; i < 3; i++){
            assert(!cli_parse(cli_module, 4, array[i]));
        }
        assert(cli_parse(cli_module, 4,  array[3]));
        cli_destroy(cli_module);
    }

    {
        cli_module_t *cli_module = cli_create();
        test_cli_register_command(cli_module);
        char **array2[4];
        //command not found
        char *argv2[] = { "git", "push", "--log", "iwue" };
        array2[0] = argv2;
        //expected value, but has gotten flag
        char *argv12[] = { "git", "push", "--gg", "-g" };
        array2[1] = argv12;
        //flag not found
        char *argv22[] = { "git", "push", "-dd", "apsod" };
        array2[2] = argv22;
        //all right
        char *argv32[] = { "git", "push", "-g", "g_arg" };
        array2[3] = argv32;
        //no command
        char *argv102[] = {"git"};
        assert(!cli_parse(cli_module, 1, argv102));
        for (int i = 0; i < 3; i++){
            assert(!cli_parse(cli_module, 4, array2[i]));
        }
        
        cli_module = cli_create();
        test_cli_register_command(cli_module);
        assert(cli_parse(cli_module, 4,  array2[3]));
        
        assert(cli_module->num_command == PUSH);
        assert(strcmp(cli_get_argument(cli_module, "gg"), "g_arg") == 0);
        assert(strcmp(cli_get_argument(cli_module, "gg"), "alsdf") != 0);
        cli_destroy(cli_module);
    }
   /* switch (cli_module->num_command){
        case CHECKOUT: 
        {
            printf("hash-object: log flag's argument =  %s\n", cli_get_argument(cli_module, "log")->array);
            break;
        }
        case PUSH: 
        {
            printf("checkout: name flag repos, argument:-- %s\n", cli_get_argument(cli_module, "repos")->array);
            break;
        }
        case BRANCH: 
        {
            printf("branch: name flag new, argument:-- %s --\n", cli_get_argument(cli_module, "new")->array);
            break;
        }
    }*/
    return 0;
}
