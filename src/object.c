#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <string.h>
#include "string_t.h"
#include "object.h"
#include "fs.h"


char hex_chars[16] = "0123456789abcdef";

// Review: call me when you finish fix review comments. 
// I want to change this *bad* prefix ssyp_string in entire project

enum obj_return_code get_blob_from_storage(char sha[SHA_STRING_LENGTH], string_t * data){
    char path[MAX_PATH_LENGTH];
    if (get_gg_root_path(path) == -1){
        return CANT_GET_ROOT_FOLDER;
    }
    strcat(path, "/objects/");
    strcat(path, sha);
    string_t buf;
    ssyp_string_initialize(&buf, 0);
    if (read_str_from_file(&buf, path) == -1){
        return CANT_OPEN_FILE;
    }
    if (strncmp(buf.array, "blob ", 5)){
        fputs("ERROR: Not blob file\n", stderr);
        ssyp_string_print(&buf);
        return NOT_BLOB_FILE;
    }
    int iter = 5;
    while (buf.array[iter] != 0){
        iter++;
    }
    int len = buf.size;
    ssyp_string_reserve(data, len - iter);
    data->size = len - iter - 1;
    strcpy(data->array, buf.array + (iter + 1));
    ssyp_string_destroy(&buf);
    return OK;
}


int cat_file(char *sha){
    string_t str;
    ssyp_string_initialize(&str, 0);
    if (strlen(sha) + 1 == SHA_STRING_LENGTH){
        int res = get_blob_from_storage(sha, &str);
        if (res != OK){
            return 0;
        }
    } else {
        return 0;
    }
    ssyp_string_print(&str);
    return 1;
}


char* itoa (int numb){
    char buf[10];
    int len = 0;
    // Review: btw, why you ever need string_t here? 
    // You can count max length of this char[] (int is not infinite).
    while (numb > 0){
        buf[len] = numb % 10 + '0';
        len++;
        numb /= 10;
    }
    char *ans = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++){
        ans[len - i - 1] = buf[i];
    }
    ans[len] = 0;
    return ans;
}


void dec_to_hex (unsigned char sha[SHA_DIGEST_LENGTH], char sha_result[SHA_STRING_LENGTH]){
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++){
        char first, second;
        unsigned char n = sha[i];
        second = hex_chars[n % 16];
        first = hex_chars[n / 16];
        sha_result[i * 2] = first;
        sha_result[i * 2 + 1] = second;
    }
    sha_result[SHA_STRING_LENGTH - 1] = '\0';
}


enum obj_return_code hash_object(char *path){
    string_t data;
    ssyp_string_initialize(&data, 0);
    if (read_str_from_file(&data, path) == -1){
        return CANT_OPEN_FILE;
    }
    char sha[SHA_STRING_LENGTH];
    enum obj_return_code return_value = save_blob_to_storage(&data, sha);
    printf("%s\n", sha);
    return return_value;
}


enum obj_return_code save_blob_to_storage(string_t * data, char sha[SHA_STRING_LENGTH]){
    char *numb = itoa(data->size);
    int ans_size = strlen(numb) + 6;
    char *ans = (char*)malloc(sizeof(char) * ans_size);
    strcpy(ans, "blob ");
    strcat(ans, numb);
    strcat(ans, "\0");
    SHA_CTX ctx; 
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, ans, ans_size);
    SHA1_Update(&ctx, data->array, data->size);
    unsigned char sha_buffer[SHA_DIGEST_LENGTH];
    SHA1_Final(sha_buffer, &ctx);
    dec_to_hex(sha_buffer, sha);
    char path[MAX_PATH_LENGTH];
    if (get_gg_root_path(path) == -1){
        return CANT_GET_ROOT_FOLDER;
    }
    strcat(path, "/objects/");
    strcat(path, sha);
    if (is_file(path) == 1){
        return ALREADY_SAVED;
    }
    FILE *f = fopen(path, "w");
    if (f == NULL){
        return CANT_OPEN_FILE;
    }
    fwrite(ans, sizeof(char), ans_size, f);
    free(ans);
    fwrite(data->array, sizeof(char), data->size, f);
    fclose(f);
    return OK;
}
