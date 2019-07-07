#ifndef FLAG_LIST_H_
#define FLAG_LIST_H_

// Review: dont need most header here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "string_t.h"

enum Commands {
    UPDATE_INDEX,
    WRITE_TREE,
    LS_FILES,
    CAT_FILE,
    HASH_OBJ,
    COUNT
};

struct flag_list;

typedef struct argument {
    int pos;
    string_t long_name;
    //! Review: short name is 1 symbol. So char would be enougth.
    string_t short_name;
    string_t help_message;
    int have_arg;
    string_t flag_argument;
} argument_t;


typedef struct {
    string_t name;
    string_t help_message;
    //? Review: why you need this?
    int num_command;
    struct flag_list *command_arguments;
} command_t;


typedef struct {
    int num_command; 
    command_t *command_list[COUNT];
    int user_argument_size;
    struct flag_list *user_argument;
} cli_module_t;

char *cli_get_argument(cli_module_t *cli_module, char *flag_name);

argument_t *find_pos_arg(command_t *command, int pos);

argument_t *find_flag(command_t *command, string_t* name_flag);

argument_t *flag_initialize();

int cli_get_command(cli_module_t *cli_module, char *name_command);

void cli_parse(cli_module_t *cli_module, int argc, char **argv);

void cli_register_command(cli_module_t *cli_module);

void add_positional_argument(cli_module_t *cli_module, enum Commands num_command, char *name, int pos, char *help_message);

void add_named_argument(cli_module_t *cli_module, enum Commands num_command, char *long_name, char *short_name, char *help_message, int have_arg);

void register_command(cli_module_t *cli_module, enum Commands num_command, char *name_command, char *help_message);

cli_module_t *cli_create();

//cli_desroy(cli_module_t *cli_module);
//! Review: cli_destroy?
#endif
