#include <stdio.h>
#include <stdlib.h>
#include "string_t.h"
#include <string.h>


void ssyp_string_reserve (string_t *str, int new_size){
    if (str->capacity > new_size){
	    return;
    }
    char *new_array = (char*)malloc(sizeof(char) * new_size);
    for (int i = 0; i < str->size; i++){
	    new_array[i] = str->array[i];
    }
    free(str->array);
    str->array = new_array;
    str->capacity = new_size;
}


void ssyp_string_print (string_t *str){
    for (int i = 0; i < str->size; i++){
        printf("%c", str->array[i]);
    }
}


void ssyp_string_char_cat (string_t *str, char *array){
    if (str == NULL || array == NULL){
        return;
    }
    string_t str2;
    ssyp_string_initialize_with_string(&str2, array);
    ssyp_string_cat(str, &str2);
}


// Returns new size of string or -1 if can't open file
int read_str_from_file (string_t *str, const char* path){
    FILE *f = fopen(path, "r");
    if (f == NULL){
	    return -1;
    }
    if (fseek(f, 0, SEEK_END) == -1){
	    return -1;
    }
    int new_size = ftell(f);
    ssyp_string_reserve (str, new_size);
    fseek(f, 0, SEEK_SET);
    fread(str->array, sizeof(char), new_size, f);
    fclose(f);
    str->size = new_size;
    return new_size;
}


int read_str_from_stream (string_t *str, FILE *f){
    if (f == NULL){
	    return -1;
    }
    int new_size = strlen(fgets(str->array, str->capacity, f));
    str->size = new_size;
    return new_size;
}


int ssyp_string_cmp (string_t *s1, string_t *s2){
    int iter = 0;
    while (iter < s1->size && iter < s2->size){
	    if (s1->array[iter] < s2->array[iter]){
	        return -1;
        } else if (s1->array[iter] > s2->array[iter]){
	        return 1;
        }
        iter++;
    }
    if (iter != s1->size){
        return -1;
    }
    if (iter != s2->size){
        return 1;
    }
    return 0;
}


void ssyp_string_cpy (string_t *from, string_t *to){
    if (from->size > to->capacity){
	    if (to->capacity * 2 > from->size){
	        ssyp_string_reserve (to, to->capacity * 2);
	    } else {
	        ssyp_string_reserve (to, from->size + 1);
	    }
    }
    for (int i = 0; i < from->size; i++){
	    to->array[i] = from->array[i];
    }
    to->size = from->size;
}


void ssyp_string_cat (string_t *s1, string_t *s2){
    if (s1->size + s2->size > s1->capacity){
	    if (s1->capacity * 2 > s1->size + s2->size){
	        ssyp_string_reserve (s1, s1->capacity * 2);
	    } else {
	        ssyp_string_reserve (s1, s1->size + s2->size + 1);
	    }
    }
    s1->array[s1->size] = s2->array[0];
    for (int iter = s1->size + 1; s1->array[iter - 1] != 0; iter++){
	    s1->array[iter] = s2->array[iter - s1->size];
    }
    s1->size += s2->size;
}


void ssyp_string_initialize (string_t *str, int init_size){
    str->array = (char*)malloc(sizeof(char) * (init_size + 1));
    str->size = 0;
    str->capacity = init_size + 1;
}


void ssyp_string_initialize_with_string (string_t *str, char *new_array){
    if (new_array == NULL){
        return;
    }
    int new_size = strlen(new_array);
    ssyp_string_initialize (str, new_size);
    for (int i = 0; i < new_size; i++){
        str->array[i] = new_array[i];
    }
    str->size = new_size;
    str->capacity = new_size;
}



void ssyp_string_destroy (string_t *str){
    free(str->array);
    str->array = NULL;
    str->size = 0;
    str->capacity = 0;
}


//Returns size of string or a short item count (or zero)
int write_str_to_file (string_t *str, const char* path){
    FILE *f = fopen(path, "w");
    if (f == NULL){
	    return -1;
    }
    int ans = fwrite(str->array, sizeof(char), str->size, f);
    fclose(f);
    return ans;
}
