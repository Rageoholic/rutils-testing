#include "rutils/debug.h"
#include "rutils/def.h"
#include "rutils/string.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* So this cmocka header is actually dumb. It needs stdarg, stdio, and
   setjmp to work */
#include <cmocka.h>

local void SplitLinesTest(void **state)
{
    ignore state;
    char strBuf[512] = {};
    const char *lineTestString1 = "This is our first test string\n"
                                  "We like test strings\r\n"
                                  "And this should work\n";
    strcpy(strBuf, lineTestString1);
    char **strArr = SplitLines(strBuf);
    for (int i = 0; i < 3; i++)
    {
        assert_non_null(strArr[i]);
    }
    assert_null(strArr[3]);

    assert_string_equal(strArr[0], "This is our first test string");
    assert_string_equal(strArr[1], "We like test strings");
    assert_string_equal(strArr[2], "And this should work");

    free(strArr);
}

local void StrCpyAndLenTest(void **state)
{
    ignore state;
    char strBuf[512];
    const char *testStr = "We work?";

    assert_true(StrCpyAndLen(strBuf, testStr, strlen(testStr)) == strlen(testStr) - 1);
    assert_true(strlen(strBuf) == strlen(testStr) - 1);
    assert_string_equal(strBuf, "We work");

    const char *otherTestStr = "Oh my god you fuck up";

    assert_true(StrCpyAndLen(strBuf, otherTestStr, 0) == 0);
    assert_string_equal(strBuf, "We work");

    /* Your *ACTUAL* use case */
    assert_true(StrCpyAndLen(strBuf, testStr, sizeof(strBuf)) == strlen(testStr));
    assert_string_equal(testStr, strBuf);
}

local void StrStartsWithTest(void **state)
{
    ignore state;

    assert_true(StrStartsWith("BlahBlahBlahBlah", "Blah", NO_GIVEN_LEN));
    assert_true(StrStartsWith("BlahBlahBlahBlah", "Blah", strlen("Blah")));

    assert_false(StrStartsWith("BlahBlahBlahBlah", "Bleh", NO_GIVEN_LEN));
    assert_false(StrStartsWith("BlahBlahBlahBlah", "Bleh", strlen("Bleh")));
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(SplitLinesTest),
        cmocka_unit_test(StrCpyAndLenTest),
        cmocka_unit_test(StrStartsWithTest),
    };

    cmocka_run_group_tests(tests, NULL, NULL);
}
