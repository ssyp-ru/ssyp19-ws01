#include <stdio.h>
#include "text_diff.h"
#include "fs.h"
#include <stdlib.h>
#include <string.h>

static int min(int first, int second, int third){
    if(first <= second && first <= third){
        return first;
    }
    if(second <= first && second <= third){
        return second;
    }
    if(third <= second && third <= first){
        return third;
    }
    return 0;
}

static diff_t **way_back(int **buf, const int len1, const int len2, diff_t **res, int *length){
    int k = len1 - 1;
    int i = len2 - 1;
    int index = -1;
    int way = -1;
    while(buf[k][i] != 0){
        if(k == 0){
            if(way == DELETE){
               res[index]->s1_len++;
               res[index]->s1_from--;
            }else{
                index++;
                res[index] = (diff_t *)malloc(sizeof(diff_t));
                res[index]->s2_len = 0;
                res[index]->s1_len = 1;
                res[index]->s2_from = k;
                res[index]->s1_from = i - 1;
                res[index]->diff_type = DELETE;
                way = DELETE;
            }
            i--;
            continue;
        }
        if(i == 0){
            if(way == ADD){
               res[index]->s2_len++;
               res[index]->s2_from--;
            }else{
                index++;
                res[index] = (diff_t *)malloc(sizeof(diff_t));
                res[index]->s1_len = 0;
                res[index]->s2_len = 1;
                res[index]->s1_from = k;
                res[index]->s2_from = i - 1;
                res[index]->diff_type = ADD;
                way = ADD;
            }
            k--;
            continue;
        }
        if( buf[k - 1][i] == min(buf[k - 1][i], buf[k][i - 1], buf[k - 1][i - 1])){
            if(way == ADD){
               res[index]->s2_len++;
               res[index]->s2_from--;
            }else{
                index++;
                res[index] = (diff_t *)malloc(sizeof(diff_t));
                res[index]->s1_len = 0;
                res[index]->s2_len = 1;
                res[index]->s1_from = k - 1;
                res[index]->s2_from = i - 1;
                res[index]->diff_type = ADD;
                way = ADD;
            }
            k--;
        }
        if (buf[k][i - 1] == min(buf[k - 1][i], buf[k][i - 1], buf[k - 1][i - 1])){
            if(way == DELETE){
               res[index]->s1_len++;
               res[index]->s1_from--;
            }else{
                index++;
                res[index] = (diff_t *)malloc(sizeof(diff_t));
                res[index]->s2_len = 0;
                res[index]->s1_len = 1;
                res[index]->s2_from = k - 1;
                res[index]->s1_from = i - 1;
                res[index]->diff_type = DELETE;
                way = DELETE;
            }
            i--;
        }
        if( buf[k - 1][i - 1] == min(buf[k - 1][i], buf[k][i - 1], buf[k - 1][i - 1])){
            if(buf[k - 1][i - 1] == buf[k][i]){
                k--;
                i--;
            }else{
                if(way == CHANGE){
                   res[index]->s2_len++;
                   res[index]->s2_from--;
                   res[index]->s1_len++;
                   res[index]->s1_from--;
                }else{
                    index++;
                    res[index] = (diff_t *)malloc(sizeof(diff_t));
                    res[index]->s1_len = 1;
                    res[index]->s2_len = 1;
                    res[index]->s1_from = k - 1;
                    res[index]->s2_from = i - 1;
                    res[index]->diff_type = CHANGE;
                    way = CHANGE;
                }
                k--;
                i--;
            }
        }
    }
    *length = index + 1;
    return res;
}

diff_t **diff_find(const char **s1, int len1, const char **s2, int len2, int *num_of_diffs){
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


diff_t **file_diff(const char *path1, const char *path2, int *num_of_diffs){
    char file1[BUF_SIZE];
    char file2[BUF_SIZE];
    if(fs_read_to_string(path1, file1) == 0 || fs_read_to_string(path2, file2) == 0){
        return 0;
    }
    char *string1[BUF_SIZE];
    char *string2[BUF_SIZE];
    int i = 0;
    int len1 = 1;
    int len2 = 1;
    string1[0] = file1;
    string2[0] = file2;
    while(file1[i] != 0){
        if(file1[i] == '\n'){
            file1[i] = 0;
            string1[len1] = &file1[i + 1];
            len1++;
        }
        i++;
    }
    len1--;
    i = 0;
    while(file2[i] != 0){
        if(file2[i] == '\n'){
            file2[i] = 0;
            string2[len2] = &file2[i + 1];
            len2++;
        }
        i++;
    }
    len2--;
    return diff_find(string1, len1, string2, len2, num_of_diffs);
}
