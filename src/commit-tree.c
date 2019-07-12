#include <stdio.h>
#include <stdlib.h>
#include "fs.h"
#include "string_t.h"
#include "object.h"
#include <openssl/sha.h>
#include "commit-tree.h"
#include "config.h"
#include <time.h>


char *get_parent(char *sha, char *str_for_parent){
    char *path = object_path(sha);
    char file_str[350];
    fs_read_to_string(path, file_str);
    int ind = 0;
    while(file_str[ind++] != '\n');
    if(file_str[ind] != 'p'){
        return "";
    }
    int par_ind = 0;
    while(file_str[ind++] != ' ');
    while(file_str[ind] != '\n'){
        str_for_parent[par_ind] = file_str[ind];
        ind++;
        par_ind++;
    }
    return str_for_parent;
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
    char *com_mes = cli_get_argument(cli_module, "message");
    if (sha == NULL || com_mes == NULL) {
        fprintf(stderr, "Not enougth arguments\n");
        exit(1);
    }
    char new_sha[SHA_STRING_LENGTH];
    commit_tree_impl(sha, parent, com_mes, new_sha);
}

void commit_tree_impl(char tree_sha[SHA_STRING_LENGTH], char parent[SHA_STRING_LENGTH], char* message, char* new_sha){
    char *sha = tree_sha;
    char *com_mes = message;
    //printf("sha %s, par %s, mes %s\n", sha, parent, com_mes);
    char pref_file[50] = "";
    char file_content[300] = "";
    
    char* name = config_get_name();
    if (name == NULL || name[0] == '\0') {
        name = getenv("GIT_AUTHOR_NAME");
        if (name == NULL) {
            fprintf(stderr, "You should put your name in config. Abort commit operation.\n");
            exit(1);
        }
    }
    char* email = config_get_email();
    if (email == NULL || email[0] == '\0') {
        email = getenv("GIT_AUTHOR_EMAIL");
        if (email == NULL) {
            fprintf(stderr, "You should put your email in config. Abort commit operation.\n");
            exit(1);
        }
    }
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char* cur_time = asctime(timeinfo);
    int time_len = strlen(cur_time);
    cur_time[time_len-1] = 0; // delete '\n'

    // Not really effective =/
    strcat(file_content, "tree ");
    strcat(file_content, sha);
    strcat(file_content, "\n");
    if (parent != NULL){
        strcat(file_content, "parent ");
        strcat(file_content, parent);
        strcat(file_content, "\n");
    }
    strcat(file_content, "author ");
    strcat(file_content, name);
    strcat(file_content, " ");
    strcat(file_content, email);
    strcat(file_content, " ");
    strcat(file_content, get_env_or_default("GIT_AUTHOR_DATE", cur_time));
    strcat(file_content, "\n");
    
    strcat(file_content, "commiter ");
    strcat(file_content, name);
    strcat(file_content, " ");
    strcat(file_content, email);
    strcat(file_content, " ");
    strcat(file_content, get_env_or_default("GIT_COMMITER_DATE", cur_time));
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

