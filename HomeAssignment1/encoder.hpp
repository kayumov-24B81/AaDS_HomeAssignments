#ifndef ENCODE_HPP
#define ENCODE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Encoder
{
    private:
        std :: string ALPHABET;
        unsigned bufferSize;
    public:
        Encoder();
        std :: string encodeSection(std :: vector<unsigned char>& data);
        std :: string encode();        
};


















#endif
