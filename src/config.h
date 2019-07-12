#ifndef CONFIG_H_
#define CONFIG_H_

#define MAX_CONFIG_ENTRY_SIZE 100

typedef struct {
    char name[MAX_CONFIG_ENTRY_SIZE];
    char email[MAX_CONFIG_ENTRY_SIZE];
} config_t ;

void config_initialize();

char* config_get_name();
char* config_get_email();

void config_set_name(char *name);
void config_set_email(char *email);

#endif
