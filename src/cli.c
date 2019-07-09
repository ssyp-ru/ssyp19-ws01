// Review: WTF?
#ifndef CLI_C_
#define CLI_C_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "list.h"
#include "string_t.h"
#include <string.h>

void test_parse_print(cli_module_t *cli_module){
    for (int i = 0; i < cli_module->size_user_arg; i++){
        printf("long_name_flag = %s\n", cli_module->user_argument[i]->long_name_flag.array);
        printf("short_name_flag = %s\n", cli_module->user_argument[i]->short_name_flag.array);
    }
}

flag_t *find_flag(command_t *command, string_t* name_flag){
    node_t *flag = command->command_arguments;
    while(flag != NULL){
        printf("%s\n", flag->value->long_name_flag.array);
        printf("%s  !!\n", name_flag->array);
        if(!ssyp_string_cmp(&flag->value->long_name_flag, name_flag) || !ssyp_string_cmp(&flag->value->short_name_flag, name_flag)){
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
        if(!ssyp_string_cmp(&cli_module->command_list[i]->name_command, &str)){
            return cli_module->command_list[i]->num_command;
        }
    }
    return -1;
}


void cli_parse(cli_module_t *cli_module, int argc, char **argv){
    int num_command = cli_get_command(cli_module, argv[1]);
    if(!(num_command + 1)){
        fprintf(stderr, "This command not register\n");
        return;
    }
    printf("%d\n", num_command);
    cli_module->num_command = num_command;
    int ind_argument = 0;
    for (int ind = 2; ind < argc; ind++){
        string_t name_flag;
        if (strncmp(argv[ind], "--", 2) == 0) {
            // Review: argv[ind] + 2
            ssyp_string_initialize_with_string(&name_flag, &argv[ind][2]);
            // Review: argv[ind][0] == '-'
        } else if (strncmp(argv[ind], "-", 1) == 0){
            ssyp_string_initialize_with_string(&name_flag, &argv[ind][1]);
        } else {
            ssyp_string_initialize_with_string(&name_flag, argv[ind]);
        }
        flag_t *flag = find_flag(cli_module->command_list[num_command], &name_flag);
        if (!flag){
            fprintf(stderr, "This flag or argument not found\n");
            return;
        }
        if (flag->have_arg) {
            ssyp_string_initialize_with_string(&flag->flag_argument, argv[++ind]);
        }
        cli_module->user_argument[ind_argument++] = flag;
    }
    cli_module->size_user_arg = ind_argument;
}


void cli_print(cli_module_t *cli_module){
    int size = COUNT - 1;
    while(size >= 0){
        if (cli_module->command_list[size] != NULL){
            node_t *flag = cli_module->command_list[size]->command_arguments;
            while(flag != NULL){
                printf("long_name_flag = %s\n", flag->value->long_name_flag.array);
                printf("short_name_flag = %s\n", flag->value->short_name_flag.array);
                printf("help_message = %s\n", flag->value->help_message.array);
                flag = flag->next;
            }
        }
        size--;
    }
}

void add_positional_argument(cli_module_t *cli_module, 
                             enum Commands num_command, 
                             char *name, int pos, 
                             char *help_message){
    // Review: what the point in this variables?
    string_t s_name;
    string_t help;
    ssyp_string_initialize_with_string(&s_name, name);
    ssyp_string_initialize_with_string(&help, help_message);
    if (cli_module->command_list[num_command] == NULL){
        printf("Command not found");
        return;
    }
    // Review: make flag_initialize
    flag_t *flag = (flag_t*)malloc(sizeof(flag_t));
    ssyp_string_initialize(&flag->long_name_flag, 1);
    ssyp_string_initialize(&flag->short_name_flag, 1);
    ssyp_string_initialize(&flag->help_message, 1);
    ssyp_string_cpy(&s_name, &flag->long_name_flag);
    ssyp_string_cpy(&s_name, &flag->short_name_flag);
    ssyp_string_cpy(&help, &flag->help_message);
    flag->pos = pos;
    node_t *arg = cli_module->command_list[num_command]->command_arguments;
    cli_module->command_list[num_command]->command_arguments = flag_node_insert(arg, flag, arg);
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

    flag_t *flag = (flag_t*)malloc(sizeof(flag_t));
    
    flag->have_arg = have_arg;

    ssyp_string_initialize(&flag->long_name_flag, 1);
    ssyp_string_initialize(&flag->short_name_flag, 1);
    ssyp_string_initialize(&flag->help_message, 1);

    ssyp_string_cpy(&l_name, &flag->long_name_flag);
    ssyp_string_cpy(&s_name, &flag->short_name_flag);
    ssyp_string_cpy(&help, &flag->help_message);

    node_t *arg = cli_module->command_list[num_command]->command_arguments;

    cli_module->command_list[num_command]->command_arguments = flag_node_insert(arg, flag, arg);

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

    ssyp_string_initialize(&command->name_command, 1);
    ssyp_string_initialize(&command->help_message, 1);

    command->num_command = num_command;

    ssyp_string_cpy(&name_com, &command->name_command);
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
    cli_module->size_user_arg = 0;
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

#endif
