#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "string_t.h"
#include <string.h>
#define MAX_PATH_LENGTH 1024
#define BUF_SIZE 1024

int file_copy(const char *path_from, const char *path_to){
    if(access(path_to, F_OK) == 0 || access(path_from, R_OK) != 0){
        return 0; //fail
    }
    FILE *file_to = fopen(path_to, "w");
    FILE *file_from = fopen(path_from, "r");
    char buf[BUF_SIZE];
    int used_size = BUF_SIZE;
    while(used_size >= BUF_SIZE){
        used_size = fread(buf, sizeof(char), BUF_SIZE, file_from);
        fwrite(buf, sizeof(char), used_size, file_to);
    }
    fclose(file_to);
    fclose(file_from);
    return 1; //success 
}

int str_del_prelast_slash(char *string){
    int last_index = -1;
    int i = 0;
    int index = -1;
    while(string[i] != 0){
        if (string[i] == '/'){
            index = last_index;
            last_index = i;
        }
        i++; 
    }
    if(index != -1){
        string[index] = 0;
    }
    return index;
}


int file_delete(const char *path){
    return remove(path) == 0;
}

int file_mkdir(const char *path){
    return mkdir(path, 0744) == 0;
}

int file_move(const char *path_from, const char *path_to){
    return rename(path_from, path_to) == 0;
}

int is_file(const char *path){
    struct stat sb;
    if (stat(path, &sb) == -1){
        return -1;
    }
    return (sb.st_mode & S_IFMT) == S_IFREG;
}

int is_directory(char *path){
    struct stat sb;
    if (stat(path, &sb) == -1){
        return -1;
    }
    return (sb.st_mode & S_IFMT) == S_IFDIR;
}

int get_gg_root_path(char *buf){
    if(getcwd(buf, MAX_PATH_LENGTH) == NULL){
        return -1;
    }
    while(strcmp("", buf) != 0){
        strcat(buf, "/.gg");        
        if(is_directory(buf) == 1){
            return 1;
        }
        if(str_del_prelast_slash(buf) == -1){
            break;
        }
    }
    return -1; 
}
