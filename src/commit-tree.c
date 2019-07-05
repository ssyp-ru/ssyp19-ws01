#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "string_t.h"
#include "object.h"
#include <openssl/sha.h>

void add_word(string_t *add, char *word, string_t *file_contents){
    ssyp_string_initialize_with_string(add, word);
    ssyp_string_cat(file_contents, add);
    ssyp_string_destroy(add);
}


void commit_tree(char *parent, char *sha, char *com_mes){
    string_t pref_file;
    string_t file_contents;
    string_t add;
    char new_sha[SHA_STRING_LENGTH];

    ssyp_string_initialize(&file_contents, 0);
    ssyp_string_initialize(&pref_file, 0);

    add_word(&add, "tree ", &file_contents);
    add_word(&add, sha, &file_contents);
    add_word(&add, "\n", &file_contents);
    if (strlen(parent) > 0){
        add_word(&add, "parent ", &file_contents);
        add_word(&add, parent, &file_contents);
        add_word(&add, "\n", &file_contents);
    }

    add_word(&add, "author ", &file_contents);
    char str[50] = "";
    strcpy(getenv("GIT_AUTHOR_NAME"), str);
    if (str == NULL){
        add_word(&add, "A_NAME", &file_contents);
    } else {
        add_word(&add, str, &file_contents);
    }

    add_word(&add, " ", &file_contents);
    strcpy(getenv("GIT_AUTHOR_EMAIL"), str);
    if (str == NULL){
        add_word(&add, "A_EMAIL", &file_contents);
    } else {
        add_word(&add, str, &file_contents);
    }

    add_word(&add, " ", &file_contents);
    strcpy(getenv("GIT_AUTHOR_DATE"), str);
    if (str == NULL){
        add_word(&add, "A_DATE", &file_contents);
    } else {
        add_word(&add, str, &file_contents);
    }

    add_word(&add, "\n", &file_contents);

    add_word(&add, "commiter ", &file_contents);
    strcpy(getenv("GIT_COMMITER_NAME"), str);
    if (str == NULL){
        add_word(&add, "C_NAME", &file_contents);
    } else {
        add_word(&add, str, &file_contents);
    }

    add_word(&add, " ", &file_contents);
    strcpy(getenv("GIT_COMMITER_EMAIL"), str);
    if (str == NULL){
        add_word(&add, "C_EMAIL", &file_contents);
    } else {
        add_word(&add, str, &file_contents);
    }

    add_word(&add, getenv("GIT_COMMITER_EMAIL"), &file_contents);
    add_word(&add, " ", &file_contents);
    strcpy(getenv("GIT_COMMITER_DATE"), str);
    if (str == NULL){
        add_word(&add, "C_DATE", &file_contents);
    } else {
        add_word(&add, str, &file_contents);
    }

    add_word(&add, "\n", &file_contents);

    add_word(&add, "\n", &file_contents);

    add_word(&add, com_mes, &file_contents);
    add_word(&add, "commit ", &pref_file);
    add_word(&add, itoa(file_contents.size), &pref_file);
    string_t crutch;
    ssyp_string_initialize(&crutch, 0);
    crutch.array[0] = '\0';
    crutch.size++;
    ssyp_string_cat(&pref_file, &crutch);

    ssyp_string_cat(&pref_file, &file_contents);

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, pref_file.array, pref_file.size);
    unsigned char sha_buffer[SHA_DIGEST_LENGTH];
    SHA1_Final(sha_buffer, &ctx);
    dec_to_hex(sha_buffer, new_sha);

    char *path = object_path(new_sha);
    write_str_to_file(&pref_file, path);
}
