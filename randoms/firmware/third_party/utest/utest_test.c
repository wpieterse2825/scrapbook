#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "third_party/utest/utest.h"

UTEST(foo, bar) {
    ASSERT_TRUE(1);
}

struct MyTestFixture {
    char  c;
    int   i;
    float f;
};

UTEST_F_SETUP(MyTestFixture) {
    utest_fixture->c = 'a';
    utest_fixture->i = 42;
    utest_fixture->f = 3.14f;

    // we can even assert and expect in setup!
    ASSERT_EQ(42, utest_fixture->i);
    EXPECT_TRUE(true);
}

UTEST_F_TEARDOWN(MyTestFixture) {
    // and also assert and expect in teardown!
    ASSERT_EQ(13, utest_fixture->i);
}

UTEST_F(MyTestFixture, a) {
    utest_fixture->i = 13;
    // teardown will succeed because i is 13...
}

//
// UTEST_F(MyTestFixture, b) {
//     utest_fixture->i = 83;
//     // teardown will fail because i is not 13!
// }
//

struct MyTestIndexedFixture {
    bool x;
    bool y;
};

UTEST_I_SETUP(MyTestIndexedFixture) {
    if (utest_index < 30) {
        utest_fixture->x = utest_index & 1;
        utest_fixture->y = (utest_index + 1) & 1;
    }
}

UTEST_I_TEARDOWN(MyTestIndexedFixture) {
    EXPECT_LE(0, utest_index);
}

UTEST_I(MyTestIndexedFixture, a, 2) {
    ASSERT_TRUE(utest_fixture->x | utest_fixture->y);
}

//
// UTEST_I(MyTestIndexedFixture, b, 42) {
//     // this will fail when the index is >= 30
//     ASSERT_TRUE(utest_fixture->x | utest_fixture->y);
// }
//

UTEST_MAIN();
