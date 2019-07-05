#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "string_t.h"
#include "object.h"
#include <openssl/sha.h>
#include "commit-tree.h"

void add_word(string_t *add, char *word, string_t *file_contents){
    ssyp_string_initialize_with_string(add, word);
    ssyp_string_cat(file_contents, add);
    ssyp_string_destroy(add);
}

char* get_env_or_default(const char* env_name, char* def_value) {
    char *env = getenv(env_name);
    if (env){
        return env;
    }
    return def_value;
}

void commit_tree(cli_module_t * cli_module){
    char *sha = cli_get_argument(cli_module, "sha");
    char *parent = cli_get_argument(cli_module, "parent");
    char *com_mes = cli_get_argument(cli_module, "messgae");
    if (sha == NULL || com_mes == NULL) {
        fprintf(stderr, "Not enougth arguments\n");
        exit(1);
    }
    string_t pref_file;
    string_t file_contents;
    string_t add;
    char new_sha[SHA_STRING_LENGTH];

    ssyp_string_initialize(&file_contents, 0);
    ssyp_string_initialize(&pref_file, 0);

    add_word(&add, "tree ", &file_contents);
    add_word(&add, sha, &file_contents);
    add_word(&add, "\n", &file_contents);
    if (parent && strlen(parent) > 0){
        add_word(&add, "parent ", &file_contents);
        add_word(&add, parent, &file_contents);
        add_word(&add, "\n", &file_contents);
    }

    add_word(&add, "author ", &file_contents);
    add_word(&add, get_env_or_default("GIT_AUTHOR_NAME", "A_NAME"), &file_contents);

    add_word(&add, " ", &file_contents);
    add_word(&add, get_env_or_default("GIT_AUTHOR_EMAIL", "A_EMAIL"), &file_contents);

    add_word(&add, " ", &file_contents);
    add_word(&add, get_env_or_default("GIT_AUTHOR_DATE", "A_DATE"), &file_contents);

    add_word(&add, "\n", &file_contents);

    add_word(&add, "commiter ", &file_contents);
    add_word(&add, get_env_or_default("GIT_COMMITER_NAME", "C_NAME"), &file_contents);

    add_word(&add, " ", &file_contents);
    add_word(&add, get_env_or_default("GIT_COMMITER_EMAIL", "C_EMAIL"), &file_contents);

    add_word(&add, " ", &file_contents);
    add_word(&add, get_env_or_default("GIT_COMMITER_DATE", "C_DATE"), &file_contents);

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

