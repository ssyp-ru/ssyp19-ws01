#include <stdio.h>
#include <openssl/sha.h>
#include "string_t.h"
#include "object.h"
#include "fs.h"


char hex_chars[16] = "0123456789abcdef";

// Review: call me when you finish fix review comments. 
// I want to change this *bad* prefix ssyp_string in entire project

enum get_blob_error_code get_blob_from_storage(char sha[SHA_STRING_LENGTH], string_t * data){
    string_t buf;
    // Review: cant you not malloc memory here (pass 0)? Seems to waste of syscall
    ssyp_string_initialize(&buf, 1);
    // Review: why BUF_SIZE? We have MAX_PATH_LENGTH
    char path[BUF_SIZE];
    if (get_gg_root_path(path) == -1){
        return READ_ERROR;
    }
    strcat(path, "/objects/");
    strcat(path, sha);
    if (read_str_from_file(&buf, path) == -1){
        return READ_ERROR;
    }
    if (strncmp(buf.array, "blob ", 5)){
        fputs("ERROR: Not blob file\n", stderr);
        ssyp_string_print(&buf);
        return NOT_BLOB;
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
    // Review: wtf? sha len should be 40 char symbols. Does this work?
    if (strlen(sha) == SHA_DIGEST_LENGTH){
        int res = get_blob_from_storage(sha, &str);
        if (res == -1){
            return 0;
        }
    } else {
        return 0;
    }
    ssyp_string_print(&str);
    return 1;
}


char* itoa (int numb){
    string_t buf;
    // Review: btw, why you ever need string_t here? 
    // You can count max length of this char[] (int is not infinite).
    ssyp_string_initialize(&buf, 0);
    while (numb > 0){
        // Review: make string_push_back_char?
        if (buf.size >= buf.capacity){
            ssyp_string_reserve(&buf, buf.capacity * 2);
        }
        buf.array[buf.size] = numb % 10 + '0';
        numb /= 10;
        buf.size++;
    }
    int len = buf.size;
    char *ans = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++){
        ans[len - i - 1] = buf.array[i];
    }
    ssyp_string_destroy(&buf);
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


enum save_blob_error_code save_blob_to_storage(string_t * data, char sha[SHA_STRING_LENGTH]){
    // Review: why you need string_t here? You khow it max size.
    string_t ans;
    ssyp_string_initialize(&ans, 16);
    char numb[10], blob[15] = "blob ";
    strcpy(ans.array, blob);
    ans.size = 5;
    strcat(ans.array, itoa(numb));
    ans.size += strlen(numb) + 1;
    SHA_CTX ctx; 
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, ans.array, ans.size);
    SHA1_Update(&ctx, data->array, data->size);
    unsigned char sha_buffer[SHA_DIGEST_LENGTH];
    SHA1_Final(sha_buffer, &ctx);
    dec_to_hex(sha_buffer, sha);
    // Review: not BUF_SIZE
    char path[BUF_SIZE];
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
    fwrite(data->array, sizeof(char), data->size, f);
    fclose(f);
    return NICE;
}
