#ifndef TEST_TEST_HELPERS_H_
#define TEST_TEST_HELPERS_H_

#include <stdio.h>
#include <stdlib.h>

static void test_ok() {
    printf("Test pass.\n");
}

static void test_fail(const char* message) {
    fprintf(stderr, "Test FAILED: %s", message);
    exit(1);
}

#endif