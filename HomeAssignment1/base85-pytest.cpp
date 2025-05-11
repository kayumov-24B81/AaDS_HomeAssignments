#include "base85.hpp"
#include <gtest/gtest.h>
#include <fstream>

TEST(RandomPyTests, EncoderTest)
{
    Encoder encoder;

    std::string decoded;
    std::ifstream dfile("decoded.txt");
    char c;
    while (dfile.get(c)) {
        decoded += c;
    }

    std::string encoded = encoder.encodeData(decoded);

    std::string expectedEncoded;
    std::ifstream efile("encoded.txt");
    while (efile.get(c)) {
        expectedEncoded += c;
    }

    EXPECT_TRUE(encoded == expectedEncoded);
}

TEST(RandomPyTests, DecoderTest)
{
    Decoder decoder;

    std::string encoded;
    std::ifstream efile("encoded.txt");
    char c;
    while (efile.get(c)) {
        encoded += c;
    }
    
    if(encoded.size() % 5 != 0)
    {
        try
        {
            EXPECT_THROW(decoder.decodeData(encoded), std::invalid_argument);
        }
        catch (const std::exception& e) 
        {
            EXPECT_EQ(e.what(), "Incorrect input data length (must be divisible by 5)");
        }
    }
    else
    {
        std :: vector<unsigned char> decodedVector = decoder.decodeData(encoded);
        std :: string decoded;
    
        for(unsigned char uc : decodedVector)
        {
            decoded += uc;
        }

        std::string expectedDecoded;
        std::ifstream dfile("decoded.txt");
        while (dfile.get(c)) 
        {
            expectedDecoded += c;
        }

        EXPECT_TRUE(decoded == expectedDecoded);
    }
}


int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
