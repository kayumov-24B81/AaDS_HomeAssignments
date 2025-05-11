#include <gtest/gtest.h>
#include "linear.hpp"

TEST(footest, footest)
{
    EXPECT_EQ(foo(), 0);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
