#ifndef STRING_T_H_
#define STRING_T_H_
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char *array;
    int size;
    int capacity;
}string_t;


void ssyp_string_reserve (string_t *str, int new_size);


int read_str_from_file (string_t *str, const char* path);


int ssyp_string_cmp (string_t *s1, string_t *s2);


void ssyp_string_cpy (string_t *from, string_t *to);


void ssyp_string_cat (string_t *s1, string_t *s2);


void ssyp_string_initialize (string_t *str, int init_size);


void ssyp_string_destroy (string_t *str);


int write_str_to_file (string_t *str, const char* path);
#endif
