#ifndef ENCODE_HPP
#define ENCODE_HPP
#include <string>
#include <vector>

class Encoder
{
    private:
        std :: string ALPHABET;
    
    public:
        Encoder();
        std :: string encode(std :: vector<unsigned char>& data);
};

















#endif
