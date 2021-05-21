#include <gtest/gtest.h>
#include "../utils.h"

TEST(Truncate0_255, InRange) {

    for (int i = 0; i <= 255; i++)
        EXPECT_EQ(truncate0_255(i), i);
}

TEST(Truncate0_255, OutOfRange) {

    EXPECT_EQ(truncate0_255(-3833638), 0);
    EXPECT_EQ(truncate0_255(92732), 255);
    EXPECT_EQ(truncate0_255(-1), 0);
    EXPECT_EQ(truncate0_255(256), 255);
}

TEST(Truncate_m100_100, InRange) {

    for (int i = -100; i <= 100; i++)
        EXPECT_EQ(truncate_m100_100(i), i);
}

TEST(Truncate_m100_100, OutOfRange) {

    EXPECT_EQ(truncate_m100_100(-101), -100);
    EXPECT_EQ(truncate_m100_100(101), 100);
    EXPECT_EQ(truncate_m100_100(-18732), -100);
    EXPECT_EQ(truncate_m100_100(132301), 100);
}

TEST(Truncate0_100, InRange) {
    for (int i = 0; i <= 100; i++)
        EXPECT_EQ(truncate0_100(i), i);
}

TEST(Truncate0_199, OutOfRange) {
    EXPECT_EQ(truncate0_100(-1), 0);
    EXPECT_EQ(truncate0_100(101), 100);
    EXPECT_EQ(truncate0_100(-1373), 0);
    EXPECT_EQ(truncate0_100(6722), 100);
}