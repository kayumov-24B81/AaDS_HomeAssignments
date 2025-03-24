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

TEST(EncoderTest, EncoderOutputTest)
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

TEST(DecoderTest, DecoderOutputTest)
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

TEST(DecoderTest, DecoderThrowLengthErrorTest)
{
    try
    {
        Decoder decoder;
        EXPECT_THROW(decoder.decodeData("87cU"), std::invalid_argument);
    }
    catch (const std::exception& e) 
    {
        EXPECT_EQ(e.what(), "Incorrect input data length (must be divisible by 5)");
    }
}

TEST(DecoderTest, DecoderThrowSymbolErrorTest)
{
    try
    {
        Decoder decoder;
        EXPECT_THROW(decoder.decodeData("87cU~"), std::invalid_argument);
    }
    catch (const std::exception& e) 
    {
        EXPECT_EQ(e.what(), "Invalid character in text");
    }
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
