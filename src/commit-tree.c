#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "string_t.h"
#include "object.h"
#include <openssl/sha.h>
#include "commit-tree.h"


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
    char *com_mes = cli_get_argument(cli_module, "message");
    if (sha == NULL || com_mes == NULL) {
        fprintf(stderr, "Not enougth arguments\n");
        exit(1);
    }
    commit_tree_impl(sha, parent, com_mes);
}
void commit_tree_impl(char tree_sha[SHA_STRING_LENGTH], char parent[SHA_STRING_LENGTH], char* message){
    char *sha = tree_sha;
    char *com_mes = message;
    printf("sha %s, par %s, mes %s\n", sha, parent, com_mes);
    char pref_file[50] = "";
    char file_content[300] = "";
    char new_sha[SHA_STRING_LENGTH];

    strcat(file_content, "tree ");
    strcat(file_content, sha);
    strcat(file_content, "\n");
    if (parent != NULL){
        strcat(file_content, "parent ");
        strcat(file_content, parent);
        strcat(file_content, "\n");
    }
    strcat(file_content, "author ");
    strcat(file_content, get_env_or_default("GIT_AUTHOR_NAME", "A_NAME"));
    strcat(file_content, " ");
    strcat(file_content, get_env_or_default("GIT_AUTHOR_EMAIL", "A_EMAIL"));
    strcat(file_content, " ");
    strcat(file_content, get_env_or_default("GIT_AUTHOR_DATE", "A_DATE"));
    strcat(file_content, "\n");
    
    strcat(file_content, "commiter ");
    strcat(file_content, get_env_or_default("GIT_COMMITER_NAME", "C_NAME"));
    strcat(file_content, " ");
    strcat(file_content, get_env_or_default("GIT_COMMITER_EMAIL", "C_EMAIL"));
    strcat(file_content, " ");
    strcat(file_content, get_env_or_default("GIT_COMMITER_DATE", "C_DATE"));
    strcat(file_content, "\n");
    strcat(file_content, "\n");
    strcat(file_content, com_mes);

    
    strcat(pref_file, "commit ");
    int len_content = strlen(file_content);
    strcat(pref_file, itoa(strlen(file_content)));
    strcat(pref_file, " ");
    int len_pref = strlen(pref_file);

    
    strcat(pref_file, file_content);
    pref_file[len_pref - 1] = '\0';
    
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, pref_file, len_pref + len_content);
    unsigned char sha_buffer[SHA_DIGEST_LENGTH];
    SHA1_Final(sha_buffer, &ctx);
    dec_to_hex(sha_buffer, new_sha);

    char *path = object_path(new_sha);
    FILE *f = fopen(path, "w");
    fwrite(pref_file, sizeof(char), len_pref + len_content, f);
    fclose(f);


}

