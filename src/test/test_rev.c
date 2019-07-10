#include "../rev.h" 
#include "../fs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "test_helpers.h"

// Review: this test currently is not working. Because rev_update
// is not working properly. Anyway. You should write something like that
// and test ALL your function and use cases. This is that tests is.

int main(){
    /*int res;
    if (1 == is_directory(".gg")) {
        printf("%d\n", res);
        test_fail("Please, do not run tests in folder where .gg exists.\nThis test will corrupt it");
        return 1;
    }
    assert(fs_mkdir(".gg"));*/
    //assert(is_directory(".gg"));
    char buf[40];
    assert(rev_parse("test228", buf));
    // Review: 
    // should 
    char new_sha[] = "17d5802036e48aa0f9ddc26988755f96739e903c";
    assert(rev_update("test228", new_sha, ""));
    assert(rev_parse("test228", buf));
    assert(strcmp(new_sha, buf) == 0);
    test_ok();
    return 0;
}
