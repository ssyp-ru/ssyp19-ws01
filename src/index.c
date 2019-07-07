#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_t.h"
#include "fs.h"
#include "object.h"
#include "index.h"
#include <openssl/sha.h>

// Use cli_module. THIS IS A PRIORITY!

enum obj_return_code update_index(char *path){
    string_t data;
    ssyp_string_initialize(&data, 0);
    read_str_from_file(&data, path);
    char sha[SHA_STRING_LENGTH];
    char index_path[MAX_PATH_LENGTH];
    if (get_gg_root_path(index_path) == -1){
        return CANT_GET_ROOT_FOLDER;
    }
    char objects_path[MAX_PATH_LENGTH];
    strcpy(objects_path, index_path);
    strcat(objects_path, "/objects/");
    enum obj_return_code return_value= save_blob_to_storage(&data, sha);
    strcat(objects_path, sha);
    if (return_value == ALREADY_SAVED){
        return ALREADY_SAVED;
    }
    strcat(index_path, "/index");
    FILE *f = fopen(index_path, "a+");
    if (f == NULL){
        return CANT_OPEN_FILE;
    }
    int buf_len = SHA_STRING_LENGTH + MAX_PATH_LENGTH + 2;
    char *buf = (char*)malloc(sizeof(char) * buf_len);
    while (fgets(buf, buf_len, f) != NULL){
        if (!strncmp(buf, sha, SHA_STRING_LENGTH)){
            free(buf);
            fclose(f);
            return ALREADY_SAVED;
        }
    }
    free(buf);
    fputs(sha, f);
    fputs(" ", f);
    fputs(path, f);
    fputs("\n", f);
    fclose(f);
    return OK;
}


void ls_files(){
    string_t data;
    ssyp_string_initialize(&data, 0);
    char path[MAX_PATH_LENGTH];
    if (get_gg_root_path(path) == -1){
        return;
    }
    strcat(path, "/index");
    read_str_from_file(&data, path);
    ssyp_string_print(&data);
}


// Review: now you should read tree object
// see object.h for tree object struct

//<mode> <filename>0<sha>
enum obj_return_code write_tree(){
    string_t data;
    ssyp_string_initialize(&data, 0);
    char index_path[MAX_PATH_LENGTH];
    if (get_gg_root_path(index_path) == -1){
        return CANT_GET_ROOT_FOLDER;
    }
    strcat(index_path, "/index");
    if (read_str_from_file(&data, index_path) == -1){
        return CANT_OPEN_FILE;
    }
    int iter = 0;
    string_t str;
    ssyp_string_initialize(&str, data.size);
    char sha[SHA_STRING_LENGTH];
    while (iter < data.size){
        ssyp_string_char_cat(&str, "100644 ");
        strncpy(sha, data.array + iter, SHA_STRING_LENGTH);
        iter += SHA_STRING_LENGTH + 1;
        while (data.array[iter] != '\n'){
            ssyp_string_char_cat(&str, &data.array[iter]);
            iter++;
        }
        ssyp_string_char_cat(&str, "\0");
        ssyp_string_char_cat(&str, sha);
        iter++;
    }
    ssyp_string_destroy(&data);
    char *str_len = itoa(str.size);
    int ans_len = strlen(str_len) + 6;
    char *ans = (char*)malloc(sizeof(char) * ans_len);
    strcpy(ans, "tree ");
    strcat(ans, str_len);
    strcat(ans, "\0");
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, ans, ans_len);
    SHA1_Update(&ctx, str.array, str.size);
    unsigned char sha_buffer[SHA_DIGEST_LENGTH];
    SHA1_Final(sha_buffer, &ctx);
    dec_to_hex(sha_buffer, sha);
    char objects_path[MAX_PATH_LENGTH];
    if (get_gg_root_path(objects_path) == -1){
        return CANT_GET_ROOT_FOLDER;
    }
    strcat(objects_path, "/objects/");
    strcat(objects_path, sha);
    if (is_file(objects_path) == 1){
        return ALREADY_SAVED;
    }
    FILE *f = fopen(objects_path, "w");
    if (f == NULL){
        return CANT_OPEN_FILE;
    }
    fwrite(ans, sizeof(char), ans_len, f);
    free(ans);
    fwrite(str.array, sizeof(char), str.size, f);
    ssyp_string_destroy(&str);
    fclose(f);
    return OK;
}
