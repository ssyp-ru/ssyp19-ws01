#include <stdio.h>
#include "string_t.h"
#include "object.h"


int get_blob_from_storage(char sha[20], string_t * data){
    string_t buf;
    ssyp_string_initialize(&buf, 1);
    if (read_str_from_file(&buf, sha) == -1){
        return -2;
    }
    if (strncmp(buf.array, "blob ", 5)){
        return -1;
    }
    int iter = 0;
    while (buf.array[iter] != 0){
        iter++;
    }
    int len = buf.size;
    ssyp_string_reserve(data, len - iter);
    data->size = 0;
    for (int i = iter + 1; i < len; i++){
        data->array[i - iter - 1] = buf.array[i];
        data->size++;
    }
    ssyp_string_destroy(&buf);
    return data->size;
}


int cat_file(char *path){
    string_t str;
    ssyp_string_initialize(&str, 1);
    if (strlen(path) == 20){
        int res = get_blob_from_storage(path, &str);
        if (res == -2){
            return -1;
        } else if (res >= 0){
            ssyp_string_print(&str);
            return 0;
        }
    }
    if (read_str_from_file(&str, path) == -1){
        return -1;
    }
    ssyp_string_print(&str);
    return 0;
}



char* itoa (int numb, char *ans){
    char buf[10];
    int len = 0;
    while (numb > 0){
        buf[len] = numb % 10 + 48;
        numb /= 10;
        len++;
    }
    for (int i = len - 1; i >= 0; i--){
        ans[len - i - 1] = buf[i];
    }
    ans[len] = 0;
    return ans;
}


void save_blob_to_storage(string_t * data, char sha[20]){
    string_t ans;
    ssyp_string_initialize(&ans, 17);
    char numb[10], blob[15] = "blob ";
    strcpy(ans.array, strcat(blob, itoa(data->size, numb)));
    ans.size = strlen(ans.array) + 1;
    ssyp_string_cat(&ans, data); 
    write_str_to_file(&ans, sha);
    ssyp_string_destroy(&ans);
}
