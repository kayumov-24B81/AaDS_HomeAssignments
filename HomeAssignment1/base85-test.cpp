#include <gtest/gtest.h>
#include "base85-test.hpp"

TEST(Base85MockTest, EncodeFromMockStreamGradual) 
{
    Encoder encoder;
    MockInputStream mockStream;

    EXPECT_CALL(mockStream, readDataPiece())
        .WillOnce(::testing::Return("Hell"))
        .WillOnce(::testing::Return("o"))
        .WillRepeatedly(::testing::Return(""));

    EXPECT_CALL(mockStream, isEndOfStream())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillRepeatedly(::testing::Return(true));

    InputStreamInterface& input = mockStream;
    std::string encoded = encoder.encodeFromInterface(input);

    EXPECT_EQ(encoded, "87cURDZ");
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
