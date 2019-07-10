#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "list.h"
#include "string_t.h"
#include <string.h>

// Review:
// So...
// You just deleted my comments without solving it...
// M'kay...
// ...

// ps. git show 971793d57e39ede64578a67101005d31e2b96bbe
// After you fix them there will be another round of review.

char *cli_get_argument(cli_module_t *cli_module, char *flag_name){
    string_t name;
    ssyp_string_initialize_with_string(&name, flag_name);
    flag_list_t *flag = cli_module->user_argument;
    while(flag != NULL){
        if(!ssyp_string_cmp(&name, &flag->value->long_name) || !ssyp_string_cmp(&name, &flag->value->short_name)){
            if (strcmp(flag->value->flag_argument.array, "") == 0) {
                return "";
            } else {

                flag->value->flag_argument.array[flag->value->flag_argument.size] = '\0';
                return flag->value->flag_argument.array;
            }
        }
        flag = flag->next;
    }
    return NULL;
}


argument_t *find_flag(command_t *command, string_t* name_flag){
    flag_list_t *flag = command->command_arguments;
    while(flag != NULL){
        if(!ssyp_string_cmp(&flag->value->long_name, name_flag) || !ssyp_string_cmp(&flag->value->short_name, name_flag)){
            return flag->value;
        }
        flag = flag->next;
    }
    return NULL;
}


int cli_get_command(cli_module_t *cli_module, char *name_command){
    string_t str;
    ssyp_string_initialize_with_string(&str, name_command);
    for(int i = 0; i < COUNT; i++){
        if(!ssyp_string_cmp(&cli_module->command_list[i]->name, &str)){
            return i;
        }
    }
    return -1;
}

argument_t *find_pos_arg(command_t *command, int pos){
    flag_list_t *flag = command->command_arguments;
    while(flag != NULL){
        if(flag->value->pos == pos){
            return flag->value;
        }
        flag = flag->next;
    }
    return NULL; 
}


int cli_parse(cli_module_t *cli_module, int argc, char **argv){
    if (argc < 2) {
        return 0 ;
    }
    int num_command = cli_get_command(cli_module, argv[1]);
    if(!(num_command + 1)){
        return 0;
    }
    cli_module->num_command = num_command;
    int pos_arg = 1;
    int was_flag = 0; // 0 - not flag, 1 - has flag now, 2 - was flag and expected flag value
    argument_t * arg_desc = NULL;
    for (int ind = 2; ind < argc; ind++){
        string_t name_flag;
        int dash_index = 0;
        if (strncmp(argv[ind], "--", 2) == 0) {
            dash_index = 2;
        } else if (argv[ind][0] == '-'){
            dash_index = 1;
        }
        if (dash_index != 0) {
            if (was_flag == 2) {
                fprintf(stderr, "Was expected flag value, get %s\n", argv[ind]);
                return 0;
            }
            ssyp_string_initialize_with_string(&name_flag, &argv[ind][dash_index]);
            was_flag = 1;
        }


        if (was_flag == 2) {
            ssyp_string_initialize_with_string(&arg_desc->flag_argument, argv[ind]);
            cli_module->user_argument =  flag_list_insert(cli_module->user_argument, arg_desc, cli_module->user_argument);
            was_flag = 0;
            continue;
        }

        if (was_flag) {
            arg_desc = find_flag(cli_module->command_list[num_command], &name_flag); 
        } else {
            arg_desc = find_pos_arg(cli_module->command_list[num_command], pos_arg++);    
        }
        if (!arg_desc){
            fprintf(stderr, "This flag or argument not found\n");
            return 0;
        }

        if (arg_desc->pos != -1) {
            ssyp_string_initialize_with_string(&arg_desc->flag_argument, argv[ind]);
            cli_module->user_argument =  flag_list_insert(cli_module->user_argument, arg_desc, cli_module->user_argument);
            was_flag = 0;
        } else if (arg_desc->have_arg == 0) {
            ssyp_string_initialize_with_string(&arg_desc->flag_argument, "");
            cli_module->user_argument =  flag_list_insert(cli_module->user_argument, arg_desc, cli_module->user_argument);
            was_flag = 0;
        } else {
            was_flag = 2;
        }
    }
    return 1;
}

argument_t *flag_initialize(){
    argument_t *flag = (argument_t*)malloc(sizeof(argument_t));
    ssyp_string_initialize(&flag->long_name, 1);
    ssyp_string_initialize(&flag->short_name, 1);
    ssyp_string_initialize(&flag->help_message, 1);
    flag->pos = -1;
    flag->have_arg = 0;
    return flag;
}

void add_positional_argument(cli_module_t *cli_module, 
                             enum Commands num_command, 
                             char *name, int pos, 
                             char *help_message){
    if (cli_module->command_list[num_command] == NULL){
        printf("Command not found");
        return;
    }
    if (find_pos_arg(cli_module->command_list[num_command], pos)){
        printf("This possition used");
        return;
    }
    string_t s_name;
    string_t help;

    ssyp_string_initialize_with_string(&s_name, name);
    ssyp_string_initialize_with_string(&help, help_message);

    argument_t *flag = flag_initialize();
    ssyp_string_cpy(&s_name, &flag->long_name);
    ssyp_string_cpy(&s_name, &flag->short_name);
    ssyp_string_cpy(&help, &flag->help_message);
    
    flag->pos = pos;
    flag_list_t *arg = cli_module->command_list[num_command]->command_arguments;

    cli_module->command_list[num_command]->command_arguments = flag_list_insert(arg, flag, arg);

    ssyp_string_destroy(&s_name);
    ssyp_string_destroy(&help);
}


void add_named_argument(cli_module_t *cli_module, 
                        enum Commands num_command, 
                        char *long_name, 
                        char *short_name, 
                        char *help_message,
                        int have_arg){
    
    if (cli_module->command_list[num_command] == NULL){
        printf("Command not found");
        return;
    }
    string_t s_name;
    string_t help;
    string_t l_name;

    ssyp_string_initialize_with_string(&l_name, long_name);
    ssyp_string_initialize_with_string(&s_name, short_name);
    ssyp_string_initialize_with_string(&help, help_message);
    
    argument_t *flag = flag_initialize();
 
    flag->have_arg = have_arg;

    ssyp_string_cpy(&l_name, &flag->long_name);
    ssyp_string_cpy(&s_name, &flag->short_name);
    ssyp_string_cpy(&help, &flag->help_message);

    flag_list_t *arg = cli_module->command_list[num_command]->command_arguments;

    cli_module->command_list[num_command]->command_arguments = flag_list_insert(arg, flag, arg);

    ssyp_string_destroy(&s_name);
    ssyp_string_destroy(&help);
    ssyp_string_destroy(&l_name);
}

void register_command(cli_module_t *cli_module, 
                      enum Commands num_command, 
                      char *name_command, 
                      char *help_message){
    string_t name_com;
    string_t help;

    ssyp_string_initialize_with_string(&name_com, name_command);
    ssyp_string_initialize_with_string(&help, help_message);

    command_t *command = (command_t*)malloc(sizeof(command_t));

    ssyp_string_initialize(&command->name, 1);
    ssyp_string_initialize(&command->help_message, 1);

    command->num_command = num_command;

    ssyp_string_cpy(&name_com, &command->name);
    ssyp_string_cpy(&help, &command->help_message);

    command->command_arguments = NULL;

    cli_module->command_list[num_command] = command;

    ssyp_string_destroy(&name_com);
    ssyp_string_destroy(&help);
}



cli_module_t *cli_create(){
    cli_module_t *cli_module = (cli_module_t*)malloc(sizeof(cli_module_t));
    for (int i = 0; i < COUNT; i++) {
        cli_module->command_list[i] = NULL;
    }
    return cli_module;
}

/*
int main(){
    cli_module_t *cli_module = cli_create();
    register_command(cli_module, CHECKOUT, 'Q', 'I');
    add_named_argument(cli_module, CHECKOUT, 'a', 'g', 'h');
    add_positional_argument(cli_module, CHECKOUT, 'G', 1, 'H');
    cli_print(cli_module);
    return 0;
}*/
