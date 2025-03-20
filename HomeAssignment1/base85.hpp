#ifndef ENCODE_HPP
#define ENCODE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

class Base85
{
    private:
        std :: string ALPHABET;
        unsigned bufferSize;
    public:
        Base85();
        std :: string encodeSection(std :: vector<unsigned char>& data);
        std :: string encode();
        std :: vector<unsigned char> decodeSection(std :: string code);
        std :: vector<unsigned char> decode();
};


















#endif
