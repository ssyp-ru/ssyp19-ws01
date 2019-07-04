#ifndef FLAG_LIST_H_
#define FLAG_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "string_t.h"

enum Commands {
    CHECKOUT,
    COMMIT,
    COUNT
};

struct node;

typedef struct flag {
    int pos;
    string_t long_name_flag;
    string_t short_name_flag;
    string_t help_message;
    int have_arg;
    string_t flag_argument;
} flag_t;


typedef struct {
    int size;
    string_t name_command;
    string_t help_message;
    int num_command;
    struct node *command_arguments;
} command_t;


typedef struct {
    int num_command; 
    command_t *command_list[COUNT];
    int size_user_arg;
    flag_t *user_argument[100];
} cli_module_t;

flag_t *find_flag(command_t *command, string_t* name_flag);

void test_parse_print(cli_module_t *cli_module);

int cli_get_command(cli_module_t *cli_module, char *name_command);

void cli_parse(cli_module_t *cli_module, int argc, char **argv);

void cli_register_command(cli_module_t *cli_module);

void cli_print(cli_module_t *cli_module);

void add_positional_argument(cli_module_t *cli_module, enum Commands num_command, char *name, int pos, char *help_message);

void add_named_argument(cli_module_t *cli_module, enum Commands num_command, char *long_name, char *short_name, char *help_message, int have_arg);

void register_command(cli_module_t *cli_module, enum Commands num_command, char *name_command, char *help_message);

cli_module_t *cli_create();
#endif
