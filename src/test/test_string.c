#include <stdio.h>
#include "../string_t.h"


int main(){
    string_t str;
    ssyp_string_initialize (&str, 1);
    if (read_str_from_file (&str, "input.txt") == -1){
	printf("ERROR in function read_str_from_file\n");
    }
    string_t str2;
    ssyp_string_initialize (&str2, 1);
    ssyp_string_cpy (&str, &str2);
    printf("%d\n", ssyp_string_cmp (&str, &str2));
    ssyp_string_cat (&str2, &str);
    if (write_str_to_file (&str2, "output.txt") == -1){
	printf("ERROR in function write_str_to_file\n");
    }
}   
