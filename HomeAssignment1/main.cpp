#include "encoder.hpp"
#include <iostream>

int main()
{
    const unsigned DATA_SIZE = 20;
    std :: vector<unsigned char> data(DATA_SIZE);
    Encoder encoder;
    std::cin.read(reinterpret_cast<char*>(data.data()), DATA_SIZE);
    std :: string encoded_data = encoder.encode(data);
    std :: cout << encoded_data << std :: endl;
    return 0;
}
