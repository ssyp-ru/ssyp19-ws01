#include "config.h"
#include "fs.h"

#include <string.h>
#include <stdio.h>

config_t config;

void delete_last_new_line(char* str) {
    int size = strlen(str);
    if (str[size-1] == '\n') {
        str[size-1] = '\0';
    }

}

FILE *get_config_file(char* option){
    char path[MAX_PATH_LENGTH];
    get_gg_root_path(path);
    strcat(path, "/config");
    FILE *f = fopen(path, option);
    return f;
}

void flush_config() {
    FILE *f = get_config_file("w");
    if (f == NULL)
        return;

    fprintf(f, "%s\n", config.name);
    fprintf(f, "%s\n", config.email);
    fclose(f);
}

void config_initialize() {
    FILE *f = get_config_file("r");
    if (f == NULL)
        return;

    fgets(config.name, MAX_CONFIG_ENTRY_SIZE, f);
    fgets(config.email, MAX_CONFIG_ENTRY_SIZE, f);
    fclose(f);
    delete_last_new_line(config.name);
    delete_last_new_line(config.email);
}

char* config_get_name() {
    return config.name;
}
char* config_get_email() {
    return config.email;
}

void config_set_name(char *name) {
    strcpy(config.name, name);
    delete_last_new_line(config.name);
    flush_config();
}

void config_set_email(char *email) {
    strcpy(config.email, email);
    delete_last_new_line(config.email);
    flush_config();
}
