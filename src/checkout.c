#include <stdio.h>
#include <string.h>
#include "object.h"
#include "string_t.h"


enum obj_return_code checkout(char *sha){
    char *objects_path = object_path(sha);
    if (strlen(object_path) == 0){
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
    char path[MAX_PATH_LENGTH];
    char file_sha[SHA_STRING_LENGTH];
    file_sha[SHA_STRING_LENGTH] = '\0';
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
        iter++;
        strncpy(file_sha, data.array + iter, SHA_STRING_LENGTH - 1);
        if (get_blob_from_storage(file_sha, &file_data) != OK){
            return CANT_OPEN_FILE;
        }
        // Review: lol...
        // Explain to me how it work
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
