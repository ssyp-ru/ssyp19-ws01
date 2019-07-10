#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "string_t.h"
#include <string.h>
#include "fs.h"

int fs_copy(const char *path_from, const char *path_to){
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

int fs_read_to_string(const char *path_from, char *str){
    if(access(path_from, R_OK) != 0){
        return 0; //fail
    }
    FILE *file_from = fopen(path_from, "r");
    int index = 0;
    int used_size = BUF_SIZE;
    while(used_size >= BUF_SIZE){
        used_size = fread(&str[index], sizeof(char), BUF_SIZE, file_from);
        index += used_size;
    }
    str[index] = 0;
    fclose(file_from);
    return 1; //success 
}

int fs_make_file(const char *path){
    FILE *file = fopen(path, "w");
    if(file == NULL){
        return 0;
    }
    fclose(file);
    return 1;
}

int fs_write_from_string(const char *path_to, const char *str){
    if(access(path_to, W_OK) != 0){
        return 0; //fail
    }
    FILE *file_to = fopen(path_to, "w");
    fwrite(str, sizeof(char), strlen(str), file_to);
    fclose(file_to);
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


int fs_delete(const char *path){
    return remove(path) == 0;
}

int fs_mkdir(const char *path){
    return mkdir(path, 0744) == 0;
}

int fs_move(const char *path_from, const char *path_to){
    return rename(path_from, path_to) == 0;
}

int is_file(const char *path){
    struct stat sb;
    if (stat(path, &sb) == -1){
        return -1;
    }
    return (sb.st_mode & S_IFMT) == S_IFREG;
}

int is_directory(const char *path){
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
        strcat(buf, _GG_DIR_NAME);        
        if(is_directory(buf) == 1){
            return 1;
        }
        if(str_del_prelast_slash(buf) == -1){
            break;
        }
    }
    return -1; 
}
