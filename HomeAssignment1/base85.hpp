#ifndef ENCODE_HPP
#define ENCODE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

class InputStreamInterface;

class Encoder
{
    private:
        std :: string ALPHABET;
        std :: vector<unsigned char> buffer;
        std :: string encodedData;
    public:
        Encoder();
        std :: string encodeBuffer();
        void handlePadding();
        void addAndCheckBuffer(char c);
        std :: string encodeStream();
        std :: string encodeData(std :: vector<char> data);
        std :: string encodeFromInterface(InputStreamInterface& input);
};

class Decoder
{
    private:
        std :: string ALPHABET;
        std :: string buffer;
        std :: vector<unsigned char> decodedData;
        std :: vector<int> charToValue;
    public:
        Decoder();
        void initializeCharToValue();
        std :: vector<unsigned char> decodeBuffer();
        void addAndCheckBuffer(char c);
        std :: vector<unsigned char> decodeData(std :: string data);
        std :: vector<unsigned char> decodeStream();
        std :: vector<unsigned char> decodeFromInterface(InputStreamInterface& input);
};

#endif
