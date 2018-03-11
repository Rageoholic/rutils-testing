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

local void CreateStringTest(void **state)
{
    ignore state;
    char *cstr = "Hello world";

    String *str = CreateString(cstr);

    assert_string_equal(str->str, cstr);
    assert_int_equal(str->len, strlen(cstr));
    assert_int_equal(str->len, str->capacity);

    DestroyString(str);
}

local void InitStringTest(void **state)
{
    ignore state;

    char *cstr = "Hello world";
    size_t len = strlen(cstr);
    String *str = malloc(len + sizeof(String) + 1);

    memset(str, 0, sizeof(str) + len);

    str->capacity = len;

    InitString(cstr, str);

    assert_string_equal(str->str, cstr);

    InitString("This better work you fucking asshole", str);

    assert_string_equal(str->str, "This better");

    assert_int_equal(str->len, len);

    InitString("Finally", str);

    assert_string_equal(str->str, "Finally");

    assert_int_equal(str->len, strlen("Finally"));

    DestroyString(str);
}

int main()
{
    const struct CMUnitTest tests[] =
        {cmocka_unit_test(CreateStringTest),
         cmocka_unit_test(InitStringTest)};

    cmocka_run_group_tests(tests, NULL, NULL);
}
