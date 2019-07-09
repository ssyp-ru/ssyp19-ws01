#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int switch_folder(char *buf, char *gg_path, char *refs_path, const char *refname, char *folder){
    str_del_prelast_slash(strcat(gg_path, "/"));
    strcat(strcat(gg_path, folder), refname);
    if(is_file(gg_path) == 1){
        strcpy(buf, gg_path);
        return 1;
    }
    return 0;
} 


int find_ref_file(const char *refname, char *buf){
    char gg_path[MAX_PATH_LENGTH];
    get_gg_root_path(gg_path);
    strcat(gg_path, "/");
    strcat(gg_path, refname);
    if(is_file(gg_path) == 1){
        strcpy(buf, gg_path);
        return 1;
    }
    str_del_prelast_slash(strcat(gg_path, "/"));
    strcat(strcat(gg_path, "/refs/"), refname);
    char refs_path[MAX_PATH_LENGTH];
    strcpy(refs_path, gg_path);
    if(is_file(gg_path) == 1){
        strcpy(buf, gg_path);
        return 1;
    }
    if(switch_folder(buf, gg_path, refs_path, refname, "/tags/")){
        return 1;
    }
    strcpy(gg_path, refs_path);
    if(switch_folder(buf, gg_path, refs_path, refname, "/heads/")){
        return 1;
    }
    strcpy(gg_path, refs_path);  
    if(switch_folder(buf, gg_path, refs_path, refname, "/remotes/")){
        return 1;
    }
    strcat(gg_path, "/HEAD");
    if(is_file(gg_path) == 1){
        strcpy(buf, gg_path);
        return 1;
    }
    return 0;

}

int rev_parse(const char *refname, char *buf){
    char path_to_ref[MAX_PATH_LENGTH];
    if(find_ref_file(refname, path_to_ref) == 0){
        return 0;
    }
    file_read_to_string(path_to_ref, buf);
    return 1;
}

// Review: this function should work differently.
// It get full ref path and fail if second arg is not sha.
// By the way, this is in man. And you can run git update-ref to check
int rev_update(const char *refname, const char *str){
    char path_to_ref[MAX_PATH_LENGTH];
    if(find_ref_file(refname, path_to_ref) == 0){
        return 0;
    }
    file_write_from_string(path_to_ref, str);
    return 1;
}
