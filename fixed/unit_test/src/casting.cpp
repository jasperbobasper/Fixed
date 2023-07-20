#include <gtest/gtest.h>
#include "../../src/fixed.hpp"

TEST(Casting, IntToIntCast) {
    Fixed<int, 16> a(123);

    EXPECT_EQ(int(a), 123);
}

TEST(Casting, IntToDoubleCast) {
    Fixed<int, 16> a(123.321);

    EXPECT_EQ(double(a), 123.321);
}


TEST(Casting, IntToLongCast) {
    Fixed<int, 16> a(123);

    EXPECT_EQ(long(a), 123);
}