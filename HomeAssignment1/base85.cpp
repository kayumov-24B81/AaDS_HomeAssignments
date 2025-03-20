#include "base85.hpp"

Base85 :: Base85()
{
    ALPHABET = R"(!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz)";
}

std :: string Base85 :: encodeData(std :: vector<unsigned char>& data)
{
    if(data.size() != 4)
    {
        throw std::invalid_argument("Invalid buffer size!");
    }
    
    unsigned num = 0;
    for (unsigned i = 0; i < 4; ++i) 
    {
        num = (num << 8) | data[i];
    }

    unsigned char values[5];
    for (int i = 4; i >= 0; --i) 
    {
        values[i] = num % 85;
        num /= 85;
    }

    std::string encodedData;
    for (int i = 0; i < 5; ++i) 
    {
        encodedData += ALPHABET[values[i]];
    }

    return encodedData;
}

std :: string Base85 :: encodeStream()
{
    std :: vector<unsigned char> buffer;
    std :: string encodedStream;
    char c;

    while (std::cin.get(c))
    {
        buffer.push_back(static_cast<unsigned char>(c));

        if(buffer.size() == 4) 
        {
             std::string encodedBuffer = encodeData(buffer);
             encodedStream += encodedBuffer;
             buffer.clear();
        }
    }
    
    if(!buffer.empty())
    {
        while(buffer.size() < 4)
        {
            buffer.push_back(0);
        }
        std :: string encodedBuffer = encodeData(buffer);
        encodedStream += encodedBuffer;;
    }
    
    return encodedStream;
}
            
std :: vector<unsigned char> Base85 :: decodeData(std :: string data)
{
    int charToValue[256];
    for(unsigned i = 0; i < 256; ++i)
    {
        charToValue[i] = -1;
    }
    
    for(unsigned i = 0; i < ALPHABET.size(); ++i)
    {
        charToValue[static_cast<unsigned char>(ALPHABET[i])] = i;
    }

    if(data.size() % 5 != 0)
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    
    std :: vector<unsigned char> decodedData;
    
    for(unsigned i = 0; i < data.size(); i += 5)
    {
        std :: string group = data.substr(i, 5);
        
        unsigned values[5];
        for(unsigned j = 0; j < 5; ++j)
        {
            char c = group[j];
            if(charToValue[static_cast<unsigned char>(c)] == -1)
            {
                throw std::invalid_argument("Invalid character in text");
            }
            values[j] = charToValue[static_cast<unsigned char>(c)];
        }
        
        unsigned num = (values[0] * std :: pow(85, 4)) + (values[1] * pow(85, 3)) + (values[2] * pow(85, 2)) + (values[3] * 85) + values[4];
        
        decodedData.push_back((num >> 24) & 0xFF);
        decodedData.push_back((num >> 16) & 0xFF);
        decodedData.push_back((num >> 8) & 0xFF);
        decodedData.push_back(num & 0xFF);
    }
    
    return decodedData;
}
        
std :: vector<unsigned char> Base85 :: decodeStream()
{
    std :: string buffer;
    std :: vector<unsigned char> decodedStream;
    char c;
    
    while(std::cin.get(c))
    {
        if(isspace(c))
        {
            continue;
        }
        
        buffer += c;
        
        if(buffer.size() == 5)
        {
            std :: vector<unsigned char> decodedBuffer = decodeData(buffer);
            decodedStream.insert(decodedStream.end(), decodedBuffer.begin(), decodedBuffer.end());
            buffer.clear();
        }   
    }

    if(!buffer.empty())
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    
    return decodedStream;
}
            
    
        
            
            
            
            
            
            
            
            
            
            
