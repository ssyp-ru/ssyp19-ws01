#include <stdio.h>
#include <string.h>
#include "object.h"
#include "string_t.h"
#include "checkout.h"


enum obj_return_code checkout(char *sha){
    char *objects_path = object_path(sha);
    if (strlen(objects_path) == 0){
        return CANT_GET_ROOT_FOLDER;
    }
    string_t data;
    ssyp_string_initialize(&data, 0);
    if (read_str_from_file(&data, objects_path) == -1){
        return CANT_OPEN_FILE;
    }
    int iter = 0;
    while (data.array[iter] != '\0' && iter < data.size){
        iter++;
    }
    iter+=6;
    char tree_sha[SHA_STRING_LENGTH];
    strncpy(tree_sha, data.array + iter, SHA_STRING_LENGTH - 1);
    ssyp_string_destroy(&data);
    iter = 0;
    tree_sha[SHA_STRING_LENGTH - 1] = '\0';
    objects_path = object_path(tree_sha);
    if (strlen(objects_path) == 0){
        return CANT_GET_ROOT_FOLDER;
    }
    ssyp_string_initialize(&data, 0);
    if (read_str_from_file(&data, objects_path) == -1){
        return CANT_OPEN_FILE;
    }
    while (data.array[iter] != '\0' && iter < data.size){
        iter++;
    }
    char path[MAX_PATH_LENGTH];
    char file_sha[SHA_STRING_LENGTH];
    file_sha[SHA_STRING_LENGTH - 1] = '\0';
    int path_iter = 0;
    string_t file_data;
    ssyp_string_initialize(&file_data, 0);
    while (iter < data.size){
        while (data.array[iter] != ' ' && iter < data.size){
            iter++;
        }
        iter++;
        path_iter = 0;
        while (data.array[iter] != '\0' && iter < data.size){
            path[path_iter] = data.array[iter];
            path_iter++;
            iter++;
        }
        path[path_iter] = '\0';
        iter++;
        strncpy(file_sha, data.array + iter, SHA_STRING_LENGTH - 1);
        if (get_blob_from_storage(file_sha, &file_data) != OK){
            return CANT_OPEN_FILE;
        }
        FILE *f = fopen(path, "w");
        if (f == NULL){
            return CANT_OPEN_FILE;
        }
        fwrite(file_data.array, sizeof(char), file_data.size, f);
        fclose(f);
    }
    ssyp_string_destroy(&data);
    ssyp_string_destroy(&file_data);
    return OK;
}
