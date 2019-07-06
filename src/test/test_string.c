#include <stdio.h>
#include "../string_t.h"


int main(){
    string_t str;
    initialize (&str, 1);
    read_str_from_file (&str, "test/test_string/input.txt");
    string_t str2;
    initialize (&str2, 1);
    ssyp_strcpy (&str, &str2);
    ssyp_strcat (&str2, &str);
    write_str_to_file (&str2, "output.txt");
    printf("this is test\n");
}   
