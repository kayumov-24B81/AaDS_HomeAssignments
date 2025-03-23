#ifndef ENCODE_HPP
#define ENCODE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

class InputStreamInterface;

class Base85
{
    private:
        std :: string ALPHABET;
    public:
        Base85();
        std :: string encodeData(std :: vector<unsigned char>& data);
        std :: string encodeStream();
        std :: string encodeFromInterface(InputStreamInterface& input);
        std :: vector<unsigned char> decodeData(std :: string data);
        std :: vector<unsigned char> decodeStream();
        std :: vector<unsigned char> decodeFromInterface(InputStreamInterface& input);
};


















#endif
