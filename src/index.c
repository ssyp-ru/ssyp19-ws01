#include <stdio.h>
#include "string_t.h"
#include "fs.h"
#include "object.h"
#include "index.h"
#include <openssl/sha.h>


int update_index(char *path){
    string_t data;
    ssyp_string_initialize(&data, 0);
    read_str_from_file(&data, path);
    char sha[SHA_STRING_LENGTH];
    if (save_blob_to_storage(&data, sha) == SAVED){
        return 1;
    }
    char index_path[BUF_SIZE];
    if (get_gg_root_path(index_path) == -1){
        return 0;
    }
    strcat(index_path, "/index");
    FILE *f = fopen(index_path, "a");
    if (f == NULL){
        return 0;
    }
    fputs(sha, f);
    fputs(" ", f);
    fputs(path, f);
    fputs("\n", f);
    fclose(f);
    return 1;
}


void ls_files(){
    string_t data;
    ssyp_string_initialize(&data, 0);
    char path[BUF_SIZE];
    if (get_gg_root_path(path) == -1){
        return;
    }
    strcat(path, "/index");
    read_str_from_file(&data, path);
    ssyp_string_print(&data);
}

//<mode> <filename>0<sha>
enum save_blob_error_code write_tree(){
    string_t ans;
    ssyp_string_initialize_with_string(&ans, "tree ");
    string_t data;
    ssyp_string_initialize(&data, 0);
    char path[BUF_SIZE];
    if (get_gg_root_path(path) == -1){
        return SAVE_ERROR;
    }
    strcat(path, "/index");
    read_str_from_file(&data, path);
    int iter = 0;
    string_t str;
    ssyp_string_initialize(&str, 0);
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
    ssyp_string_char_cat(&ans, str_len);
    ssyp_string_char_cat(&ans, "\0");
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, ans.array, ans.size);
    SHA1_Update(&ctx, str.array, str.size);
    unsigned char sha_buffer[SHA_DIGEST_LENGTH];
    SHA1_Final(sha_buffer, &ctx);
    dec_to_hex(sha_buffer, sha);
    if (get_gg_root_path(path) == -1){
        return SAVE_ERROR;
    }
    strcat(path, "/objects/");
    strcat(path, sha);
    if (is_file(path) == 1){
        return SAVED;
    }
    FILE *f = fopen(path, "w");
    if (f == NULL){
        return SAVE_ERROR;
    }
    fwrite(ans.array, sizeof(char), ans.size, f);
    ssyp_string_destroy(&ans);
    fwrite(str.array, sizeof(char), str.size, f);
    ssyp_string_destroy(&str);
    fclose(f);
    return NICE;
}
