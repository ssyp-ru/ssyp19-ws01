#include <stdio.h>
#include "cli.h"
#include "object.h"
#include "fs.h"
#include "commit-tree.h"
#include <string.h>


void git_log(cli_module_t *cli_module){
    char path[MAX_PATH_LENGTH] = "";
    get_gg_root_path(path);
    strcat(path, "/refs/heads/branch");
    char parent[SHA_STRING_LENGTH];
    fs_read_to_string(path, parent);
    parent[SHA_STRING_LENGTH - 1] = '\0';
    char content[350];
    int i = 0;
    while(strcmp(parent, "") != 0){
        strcpy(path, object_path(parent));
        fs_read_to_string(path, content);
        while(content[i++] != '\0');
        printf("commit %s\n%s\n--------------------------\n", parent, &content[i]);
        strcpy(parent, get_parent(parent, parent));
        i = 0;
    }
}
