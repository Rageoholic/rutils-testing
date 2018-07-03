#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "rutils/file.h"

static void TestBaseName(void **state)
{
    ignore state;
    char destBuf1[512] = {};
    char fileName[] = "/blah/foo/fee";
    assert_string_equal("fee", BaseName(destBuf1, sizeof(destBuf1),
                                        fileName, NO_GIVEN_LEN));

    char destBuf2[512] = {};
    assert_string_equal("fee", BaseName(destBuf2, sizeof(destBuf2),
                                        fileName, strlen(fileName)));

    char destBuf3[512] = {};
    assert_string_equal("fe", BaseName(destBuf3, 3,
                                       fileName, strlen(fileName)));

    char destBuf4[512] = {};
    assert_string_equal("", BaseName(destBuf4, 1,
                                     fileName, strlen(fileName)));

    char destBuf5[] = "blehbleh";
    assert_string_equal("blehbleh", BaseName(destBuf5, 0,
                                             fileName, strlen(fileName)));
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(TestBaseName),
    };

    cmocka_run_group_tests(tests, NULL, NULL);
}
