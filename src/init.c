#include <stdio.h>
#include "fs.h"
#include <string.h>
#include <unistd.h>
#include "init.h"

void sub_init(char *path, const char *folder){
    //str_del_prelast_slash(strcat(path, "/"));
    strcat(path, folder);
    fs_mkdir(path);
    str_del_prelast_slash(strcat(path, "/"));
}

int init(){
    char buf[MAX_PATH_LENGTH];
    if(getcwd(buf, MAX_PATH_LENGTH) == NULL){
        return 0;
    }
    strcat(buf, GG_DIR_NAME);
    if(is_directory(buf) == 1){
        return 0;
    }
    fs_mkdir(buf);
    sub_init(buf, "/objects");
    return 1;
}


