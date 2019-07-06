#ifndef STRING_T_H_
#define STRING_T_H_
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char *array;
    int size;
    int capacity;
}string_t;


void reserve (string_t *str, int new_size);


int read_str_from_file (string_t *str, const char* path);


int ssyp_strcmp (string_t *s1, string_t *s2);


void ssyp_strcpy (string_t *from, string_t *to);


void ssyp_strcat (string_t *s1, string_t *s2);


void initialize (string_t *str, int init_size);


void destroy (string_t *str);


int write_str_to_file (string_t *str, const char* path);
#endif
