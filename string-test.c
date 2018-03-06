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

    DestroyString(str);
}

local void CreateStringExTest(void **state)
{
    ignore state;

    char *cstr = "Hello world";
    size_t len = +strlen(cstr);
    String *str = malloc(len + sizeof(String) + 1);

    memset(str, 0, len);

    CreateStringEx(cstr, str, len);

    assert_string_equal(str->str, cstr);

    CreateStringEx("This better work you fucking asshole", str, len);

    assert_string_equal(str->str, "This better");

    assert_int_equal(str->len, len);

    CreateStringEx("Finally", str, len);

    assert_string_equal(str->str, "Finally");

    assert_int_equal(str->len, strlen("Finally"));

    DestroyString(str);
}
int main()
{
    const struct CMUnitTest tests[] =
        {cmocka_unit_test(CreateStringTest),
         cmocka_unit_test(CreateStringExTest)};

    cmocka_run_group_tests(tests, NULL, NULL);
}
