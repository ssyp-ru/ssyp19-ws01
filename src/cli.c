#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Commands {
    CHECKOUT,
    COUNT
};


typedef struct {
    int pos;
    char user_name_flag;
    char long_name_flag;
    char short_name_flag;
    char *argument[30];
    char help_message;
} flag_t;


typedef struct { 
    int size;
    char user_name_command;
    char name_command;
    char help_message;
    int num_command;
    flag_t *command_arguments[50];
} command_t;


typedef struct {
    int size;
    command_t *command_list[COUNT];
    char *all_argument;
} cli_module_t;

/*
command_t *get_command(cli_module_t *cli_module,char command_name){
    int ind = 0;
    while(cli_module->command_list[++ind]->name_command != command_name);
    if(cli_module->command_list[ind]->name_command == command_name){
        return cli_module->command_list[ind];
    }
    return NULL;
}


flag_t *right_flag(cli_module_t* cli_module, char flag_name, command_t* command){
    int ind = 0;
    flag_t *flag = command->command_arguments[ind];
    while(flag->shot_name_flag != flag_name && flag->long_name_flag !+ flag_name){
        if(command->command_arguments[ind] == NULL){
            return NULL;
        }
        flag = command->command_arguments[++ind]->short_name_flag;
    }
    return flag;
}
*/

void cli_parse(cli_module_t *cli_module, int argc, char *argv);


void cli_register_command(cli_module_t *cli_module);


void cli_print(cli_module_t *cli_module){
    int size = cli_module->size - 1;
    while(size >= 0){
        int com_size = cli_module->command_list[size]->size - 1;
        while(com_size >= 0){
            printf("long_name_flag = %c\n", cli_module->command_list[size]->command_arguments[com_size]->long_name_flag);
            printf("short_name_flag = %c\n", cli_module->command_list[size]->command_arguments[com_size]->short_name_flag);
            printf("help_message = %c\n", cli_module->command_list[size]->command_arguments[com_size]->help_message);
            com_size--;
        }
        size--;
    }
}

void add_positional_argument(cli_module_t *cli_module, enum Commands num_command, char name, int pos, char help_message){
    flag_t *flag = (flag_t*)malloc(sizeof(flag_t));
    int ind = -1;
    while(cli_module->command_list[++ind]->num_command != num_command);
    flag->long_name_flag = name;
    flag->short_name_flag = name;
    flag->help_message = help_message;
    flag->pos = pos;
    cli_module->command_list[ind]->command_arguments[cli_module->command_list[ind]->size++] = flag;
}


void add_named_argument(cli_module_t *cli_module, enum Commands num_command, char long_name, char short_name, char help_message){
    flag_t *flag = (flag_t*)malloc(sizeof(flag_t));
    int ind = -1;
    while(cli_module->command_list[++ind]->num_command != num_command);
    flag->long_name_flag = long_name;
    flag->short_name_flag = short_name;
    flag->help_message = help_message;
    cli_module->command_list[ind]->command_arguments[cli_module->command_list[ind]->size++] = flag;
}

void register_command(cli_module_t *cli_module, enum Commands num_command, char name_command, char help_message){
    command_t *command = (command_t*)malloc(sizeof(command_t));
    command->num_command = num_command;
    command->name_command = name_command;
    command->help_message = help_message;
    command->size = 0;
    cli_module->command_list[cli_module->size++] = command;
}



cli_module_t *cli_create(){
    cli_module_t *cli_module = (cli_module_t*)malloc(sizeof(cli_module_t));
    cli_module->size = 0;
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
} */
