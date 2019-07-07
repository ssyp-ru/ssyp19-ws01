#ifndef STRING_T_H_
#define STRING_T_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char *array;
    int size;
    int capacity;
} string_t;


int read_str_from_file (string_t *str, const char* path);

int read_str_from_stream (string_t *str, FILE *f);

int write_str_to_file (string_t *str, const char* path);

void ssyp_string_reserve (string_t *str, int new_size);

void ssyp_string_add_str_in_end (string_t *str, char *array);

int ssyp_string_cmp (string_t *s1, string_t *s2);

void ssyp_string_cpy (string_t *from, string_t *to);

void ssyp_string_cat (string_t *s1, string_t *s2);

void ssyp_string_initialize (string_t *str, int init_size);

void ssyp_string_initialize_with_string (string_t *str, char *new_array);

void ssyp_string_destroy (string_t *str);


#endif
