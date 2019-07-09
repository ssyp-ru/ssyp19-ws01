#ifndef OBJECT_H_
#define OBJECT_H_

#include "string_t.h"

#define MAX_PARENT_COUNT 10

enum object_type {
    BLOB,
    TREE,
    COMMIT
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

void get_blob_from_storage(char sha[20], string_t * data);
void save_blob_to_storage(string_t * data, char sha[20]);

// void get_tree_from_storage(char sha[20], vector_tree_t * tree_object);
// void set_tree_to_storage(vector_tree_t * tree_object, char sha[20]);

void get_commit_from_storage(char sha[20], commit_object_t * object);
void set_commit_to_storage(commit_object_t * object, char sha[20]);

#endif