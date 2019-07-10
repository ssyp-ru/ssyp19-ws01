#ifndef OBJECT_H_
#define OBJECT_H_
#include <openssl/sha.h>
#include "string_t.h"
#include "fs.h"

#define MAX_PARENT_COUNT 10
#define SHA_STRING_LENGTH (SHA_DIGEST_LENGTH * 2 + 1)


// Review: well, I guess I dont need to review 8_hash_object ...

enum object_type {
    BLOB,
    TREE,
    COMMIT
};

// Review: better make one enum with all kind of errors
// something like
// enum obj_return_code {
//      OK,
//      CANT_GET_ROOT_FOLDER,
//      ...
//};
enum get_blob_error_code {
    READ_ERROR,
    NOT_BLOB,
    OK    
};

enum save_blob_error_code {
    SAVE_ERROR,
    SAVED,
    NICE
};

typedef struct {
    char *name;
    char *mode;
    char *sha;
    enum object_type type; // can be BLOB or TREE
} tree_entry_t;

typedef struct {
    char tree_sha[20];
    char parent_sha[MAX_PARENT_COUNT][20];
    string_t message;

    string_t author_name;
    string_t author_email;
    string_t author_date;

    string_t commiter_name;
    string_t commiter_email;
    string_t commiter_date;
} commit_object_t;

FILE* get_object_type(char sha[20], int do_not_close_file);

enum get_blob_error_code get_blob_from_storage(char sha[SHA_STRING_LENGTH], string_t * data);
enum save_blob_error_code save_blob_to_storage(string_t * data, char sha[SHA_STRING_LENGTH]);

int cat_file(char *path);

char* itoa(int numb);

void dec_to_hex(unsigned char sha[SHA_DIGEST_LENGTH], char sha_result[SHA_STRING_LENGTH]);

// void get_tree_from_storage(char sha[20], vector_tree_t * tree_object);
// void set_tree_to_storage(vector_tree_t * tree_object, char sha[20]);

void get_commit_from_storage(char sha[20], commit_object_t * object);
void set_commit_to_storage(commit_object_t * object, char sha[20]);

#endif
