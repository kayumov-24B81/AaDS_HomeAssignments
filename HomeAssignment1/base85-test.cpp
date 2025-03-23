#include <gtest/gtest.h>
#include "base85-test.hpp"

TEST(EncoderMockTest, EncodeFromMockStreamGradual) 
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

TEST(EncoderMockTest, EncoderOutputTest)
{
    Encoder encoder;
    std::ostringstream mockedOstream;
    auto coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(mockedOstream.rdbuf());
    
    std :: string encoded = encoder.encodeData("Hello");
    std :: cout << encoded << std :: endl;

    std::cout.rdbuf(coutBuf);

    EXPECT_EQ(mockedOstream.str(), "87cURDZ\n");
}

TEST(DecoderMockTest, DecodeFromMockStreamGradual)
{
    Decoder decoder;
    MockInputStream mockStream;

    EXPECT_CALL(mockStream, readDataPiece())
        .WillOnce(::testing::Return("87cURDeWWsB5"))
        .WillOnce(::testing::Return("_^!"))
        .WillRepeatedly(::testing::Return(""));

    EXPECT_CALL(mockStream, isEndOfStream())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillRepeatedly(::testing::Return(true));

    InputStreamInterface& input = mockStream;
    std :: vector<unsigned char> decoded = decoder.decodeFromInterface(input);
    std :: string word = "";
    for(char c : decoded)
    {
        word += c;
    }

    EXPECT_EQ(word, "Helloiamgood");
}

TEST(DecoderMockTest, DecoderOutputTest)
{
    Decoder decoder;
    std::ostringstream mockedOstream;
    auto coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(mockedOstream.rdbuf());
    
    std :: vector<unsigned char> decoded = decoder.decodeData("87cURDeWWsB5_^!");
    for(unsigned char byte : decoded)
    {
        std :: cout << byte;
    }
        
    std :: cout << std :: endl;

    std::cout.rdbuf(coutBuf);

    EXPECT_EQ(mockedOstream.str(), "Helloiamgood\n");
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
