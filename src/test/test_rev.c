#include "rev.h" 
#include "fs.h"
#include <stdio.h>


int main(){
    char buf[MAX_PATH_LENGTH];
    int res2 = rev_update("test228", "228758213");
    int res = rev_parse("test228", buf);
    printf("%d %d\n%s\n", res, res2,  buf);
    return 0;
}
