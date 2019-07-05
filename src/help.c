#include <stdio.h>
#include "cli.h"
#include "string_t.h"
#include "list.h"

void help(cli_module_t *cli_module){
    int i = 0;
    while(i != COUNT){
        ssyp_string_print(&cli_module->command_list[i]->name);
        printf("\n");
        flag_list_t *flags = cli_module->command_list[i]->command_arguments;
        while(flags != NULL){
            if(flags->value->pos != -1){
                printf("name positional argument ");
                ssyp_string_print(&flags->value->long_name);
                printf(", help message");
                ssyp_string_print(&flags->value->help_message);
            } else {
                printf("long name flag --");
                ssyp_string_print(&flags->value->long_name);
                printf(", short name flag -");
                ssyp_string_print(&flags->value->short_name);
                printf(", help message");
                ssyp_string_print(&flags->value->help_message);
            }
            printf("\n");
            flags = flags->next;
        }
        printf("\n");
        i++;
    }
}
