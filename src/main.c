#include "text_diff.h"
#include <stdio.h>

int printim(diff_t **diffs, int num){
    for(int i = num - 1; i >= 0; i--){
        printf("(%d %d %d %d %d)\n", diffs[i]->s1_from, diffs[i]->s1_len, diffs[i]->s2_from, diffs[i]->s2_len, diffs[i]->diff_type );
    
}
}

int main(){
    char *s1[9];
    s1[0] = "i";
    s1[1] = "n"; 
    s1[2] = "t";
    s1[3] = "e";
    s1[4] = "n";
    s1[5] = "t";
    s1[6] = "i";
    s1[7] = "o";
    s1[8] = "n";
    char *s2[9];
    s2[0] = "e";
    s2[1] = "x";
    s2[2] = "e";
    s2[3] = "c";
    s2[4] = "u";
    s2[5] = "t";
    s2[6] = "i";
    s2[7] = "o";
    s2[8] = "n";
    int a;
    char **strings[2];
    diff_t **res = file_diff("file1.txt", "file2.txt", &a, strings);//diff_find(s1, 9, s2, 9, &a);
    //diff_print(strings[0], strings[1], res, a);
    printf("\n");
    printim(res, a);
    return 0;
}
