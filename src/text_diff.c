#include <stdio.h>
#include "text_diff.h"
#include "fs.h"
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "index.h"

static int min(int first, int second, int third){   
    if(first <= second){
        if(first <= third){
            return first;
        }else{
            return third;
        }
    }else{
        if(second <= third){
            return second;
        }else{
            return third;
        }
    }
}

int diff_print(char **s1, char **s2, diff_t **diffs, int n){
    for(int i = n - 1; i >= 0; i--){
        switch(diffs[i]->diff_type){
            case DIFF_ADD:
                for(int k = diffs[i]->s2_from; k < diffs[i]->s2_from + diffs[i]->s2_len; k++){
                    printf("+%s\n", s2[k]);
                }
                break;
            case DELETE:
                for(int k = diffs[i]->s1_from; k < diffs[i]->s1_from + diffs[i]->s1_len; k++){
                    printf("-%s\n", s1[k]);
                }
                break;
            case CHANGE:
                for(int k = diffs[i]->s1_from; k < diffs[i]->s1_from + diffs[i]->s1_len; k++){
                    printf("-%s\n", s1[k]);
                }
                for(int k = diffs[i]->s2_from; k < diffs[i]->s2_from + diffs[i]->s2_len; k++){
                    printf("+%s\n", s2[k]);
                }
                break;
            case NOT_CHANGE:
                for(int k = diffs[i]->s1_from; k < diffs[i]->s1_from + diffs[i]->s1_len; k++){
                    printf(" %s\n", s1[k]);
                }
                break;
        }
    }
    return 0;
}

diff_t * create_diff(int from1, int len1, int from2, int len2, enum diff_types type) {
    diff_t * d = (diff_t *)malloc(sizeof(diff_t));
    d->s1_from = from1;
    d->s1_len = len1;
    d->s2_from = from2;
    d->s2_len = len2;
    d->diff_type = type;
    return d;
}

//char **get_second_str(char **s1; diff_t **diffs)

static diff_t **way_back(int **buf, int len1, int len2, diff_t **res, int *length){
    int k = len1 - 1;
    int i = len2 - 1;
    int index = -1;
    int way = -1;
    while(i != 0 && k != 0){
        if(i == 0){
            if(way == DELETE){
               res[index]->s1_len++;
               res[index]->s1_from--;
            }else{
                index++;
                res[index] = create_diff(k - 1, 1, i, 0, DELETE);
                way = DELETE;
            }
            k--;
            continue;
        }
        if(k == 0){
            if(way == DIFF_ADD){
               res[index]->s2_len++;
               res[index]->s2_from--;
            }else{
                index++;
                res[index] = create_diff(k, 0, i - 1, 1, DIFF_ADD);
                way = DIFF_ADD;
            }
            i--;
            continue;
        }
        if( buf[k - 1][i] == min(buf[k - 1][i], buf[k][i - 1], buf[k - 1][i - 1])){
            if(way == DELETE){
               res[index]->s1_len++;
               res[index]->s1_from--;
            }else{
                index++;
                res[index] = create_diff(i - 1, 1, k - 1, 0, DELETE);
                way = DELETE;
            }
            k--;
            continue;
        }
        if (buf[k][i - 1] == min(buf[k - 1][i], buf[k][i - 1], buf[k - 1][i - 1])){
            if(way == DIFF_ADD){
               res[index]->s2_len++;
               res[index]->s2_from--;
            }else{
                index++;
                res[index] = create_diff(k - 1, 0, i - 1, 1, DIFF_ADD);
                way = DIFF_ADD;
            }
            i--;
            continue;
        }
        if( buf[k - 1][i - 1] == min(buf[k - 1][i], buf[k][i - 1], buf[k - 1][i - 1])){
            if(buf[k - 1][i - 1] == buf[k][i]){
                if(way == NOT_CHANGE){
                   res[index]->s2_len++;
                   res[index]->s2_from--;
                   res[index]->s1_len++;
                   res[index]->s1_from--;
                }else{
                    index++;
                    res[index] = create_diff(k - 1, 1, i - 1, 1, NOT_CHANGE);
                    way = NOT_CHANGE;
                }
                k--;
                i--;
                continue;
            }else{
            if(way == CHANGE){
               res[index]->s2_len++;
               res[index]->s2_from--;
               res[index]->s1_len++;
               res[index]->s1_from--;
            }else{
                index++;
                res[index] = create_diff(k - 1, 1, i - 1, 1, CHANGE);
                way = CHANGE;
            }
            k--;
            i--;
            continue;
            }
        }
    }
    *length = index + 1;
    return res;
}

diff_t **diff_find(char **s1, int len1, char **s2, int len2, int *num_of_diffs){
    len1++;
    len2++;
    int **buf = (int **)malloc(sizeof(int *) * (len1));
    for(int i = 0; i < len1; i++){
        buf[i] = (int *)malloc(sizeof(int) * (len2));
        buf[i][0] = i;
    }
    for(int i = 1; i < len2; i++){
        buf[0][i] = i;
    }
    int container = 0; 
    for(int k = 1; k < len1; k++){
        for(int i = 1; i < len2; i++){
            if(strcmp(s1[k - 1], s2[i - 1]) == 0){
               container = buf[k - 1][i - 1];
            }else{
               container = buf[k - 1][i - 1] + 2;
            }
            buf[k][i] = min(buf[k - 1][i] + 1, buf[k][i - 1] + 1, container);
        }
    }
    diff_t **res = way_back(buf, len1, len2, (diff_t **)malloc(sizeof(diff_t *) * buf[len1 - 1][len2 - 1]), num_of_diffs);
    for(int i = 0; i < len1; i++){
        free(buf[i]);
    }
    free(buf);
    return res;
}



void split_content(char *file, char **string, int *size) {
    int i = 0;
    int len = 0;
    //string[0] = file;
    //char *ptr = index(file, '\n');
    int prev = -1;
    while(file[i] != 0){
        if(file[i] == '\n'){
            if(prev == -1){
                prev = i;
                file[i] = 0;
                strcpy(string[len], file);
            }else{
                file[i] = 0;
                strcpy(string[len], &file[prev + 1]);
                prev = i;
            }
            len++;
        }
        i++;
    }
    //len--;
    *size = len;
}

void split_file_content(const char* file_path, char ** string, int *size) {
    char file[BUF_SIZE];
    if(fs_read_to_string(file_path, file) == 0){
        return;
    }
    int i = 0;
    int len = 0;
    //string[0] = file;
    //char *ptr = index(file, '\n');
    int prev = -1;
    while(file[i] != 0){
        if(file[i] == '\n'){
            if(prev == -1){
                prev = i;
                file[i] = 0;
                strcpy(string[len], file);
            }else{
                file[i] = 0;
                strcpy(string[len], &file[prev + 1]);
                prev = i;
            }
            len++;
        }
        i++;
    }
    //len--;
    *size = len;
}

char ** allocate_string_matrix(int size) {
    char ** string;
    string = (char**)malloc(sizeof(char**) * size);
    for (int i = 0; i < size; i++) {
        string[i] = (char*)malloc(sizeof(char*) * size);
    }
    return string;
}

diff_t **file_diff(const char *path1, const char *path2, int *num_of_diffs){
    char ** string1 = allocate_string_matrix(BUF_SIZE);
    char ** string2 = allocate_string_matrix(BUF_SIZE);
    int len1 = 1;
    int len2 = 1;
    split_file_content(path1, string1, &len1);
    split_file_content(path2, string2, &len2);
    diff_t ** d = diff_find(string1, len1, string2, len2, num_of_diffs);
    diff_print(string1, string2, d, *num_of_diffs);
    return d;
}

void diff(){
    FILE *index = fopen(get_index_path(), "r");
    if (index == NULL) {
        return;
    }
    int num_of_diffs = 0;
    string_t buf;
    ssyp_string_initialize(&buf, 0);
    char ** string1 = allocate_string_matrix(BUF_SIZE);
    char ** string2 = allocate_string_matrix(BUF_SIZE);
    char indexStr[MAX_PATH_LENGTH + SHA_STRING_LENGTH + 1]; //aeeeeee nice constants
    char buf_char[BUF_SIZE];
    while(fgets(indexStr, MAX_PATH_LENGTH + SHA_STRING_LENGTH + 1, index) != NULL){
        printf("========================================================\n");
        int len1 = 1;
        int len2 = 1;
        char sha[SHA_STRING_LENGTH];
        char file_path[MAX_PATH_LENGTH];
        sscanf(indexStr, "%s%s", sha, file_path);
        get_blob_from_storage(sha, &buf);
        strncpy(buf_char, buf.array, buf.size);
        split_file_content(file_path, string1, &len1);
        split_content(buf_char, string2, &len2);
        diff_t ** d = diff_find(string2, len2, string1, len1, &num_of_diffs);
        diff_print(string2, string1, d, num_of_diffs);
    }

}
