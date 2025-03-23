#include "base85-test.hpp"

Encoder :: Encoder()
{
    ALPHABET = R"(!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz)";
}

std :: string Encoder :: encodeBuffer()
{
    if(buffer.size() != 4)
    {
        throw std::invalid_argument("Invalid buffer size!");
    }
    
    unsigned num = 0;
    for (unsigned i = 0; i < 4; ++i) 
    {
        if(i < 4)
        {
            num = (num << 8) | buffer[i];
        }
        else
        {
            num <<= 8;
        }
    }

    unsigned char values[5];
    for (int i = 4; i >= 0; --i) 
    {
        values[i] = num % 85;
        num /= 85;
    }

    std::string encodedBuffer;
    for (int i = 0; i < 5; ++i) 
    {
        encodedBuffer += ALPHABET[values[i]];
    }
    return encodedBuffer;
}

void Encoder :: handlePadding()
{
    if(!buffer.empty())
    {
        unsigned padding = 4 - buffer.size();
        while(buffer.size() < 4)
        {
            buffer.push_back(0);
        }
        std :: string encodedBuffer = encodeBuffer();
        encodedData += encodedBuffer.substr(0, 5 - padding);
    }
}

void Encoder :: addAndCheckBuffer(char c)
{
    buffer.push_back(static_cast<unsigned char>(c));
    if(buffer.size() == 4) 
    {
         std::string encodedBuffer = encodeBuffer();
         encodedData += encodedBuffer;
         buffer.clear();
    }
}

std :: string Encoder :: encodeStream()
{
    encodedData.clear();
    char c;
    while (std::cin.get(c))
    {
        addAndCheckBuffer(c);
    }
    handlePadding();
    return encodedData;
}

std :: string Encoder :: encodeData(std :: vector<char> data)
{
    encodedData.clear();
    for(char c : data)
    {
        addAndCheckBuffer(c);
    }
    handlePadding();
    return encodedData;
}

std :: string Encoder ::  encodeFromInterface(InputStreamInterface& input)
{
    encodedData.clear();
    while (!input.isEndOfStream())
    {
        std :: string piece = input.readDataPiece();
        if(piece.empty())
        {
            break;
        }
        for(char c : piece)
        {
            addAndCheckBuffer(c);
        }
    }
    handlePadding();
    return encodedData;
}
    
  
Decoder :: Decoder()
{
    ALPHABET = R"(!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz)";
}

void Decoder :: initializeCharToValue()
{
    for(unsigned i = 0; i < 256; ++i)
    {
        charToValue.push_back(-1);
    }
    
    for(unsigned i = 0; i < ALPHABET.size(); ++i)
    {
        charToValue[static_cast<unsigned char>(ALPHABET[i])] = i;
    }
}

std :: vector<unsigned char> Decoder :: decodeBuffer()
{
    if(buffer.size() == 0)
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    std :: vector<unsigned char> decodedBuffer;
    for(unsigned i = 0; i < buffer.size(); i += 5)
    {
        std :: string group = buffer.substr(i, 5);
        
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
        
        decodedBuffer.push_back((num >> 24) & 0xFF);
        decodedBuffer.push_back((num >> 16) & 0xFF);
        decodedBuffer.push_back((num >> 8) & 0xFF);
        decodedBuffer.push_back(num & 0xFF);
    }
    return decodedBuffer;
}

void Decoder :: addAndCheckBuffer(char c)
{
    buffer += c;
    if(buffer.size() == 5)
    {
        std :: vector<unsigned char> decodedBuffer = decodeBuffer();
        decodedData.insert(decodedData.end(), decodedBuffer.begin(), decodedBuffer.end());
        buffer.clear();
    }
}

std :: vector<unsigned char> Decoder :: decodeData(std :: string data)
{
    decodedData.clear();
    initializeCharToValue();
    for(char c : data)
    {
        if(isspace(c))
        {
            continue;
        }
        addAndCheckBuffer(c);
    }
    if(!buffer.empty())
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    return decodedData;
}
        
std :: vector<unsigned char> Decoder :: decodeStream()
{
    decodedData.clear();
    initializeCharToValue();
    char c;
    while(std::cin.get(c))
    {
        if(isspace(c))
        {
            continue;
        }
        addAndCheckBuffer(c);
    }
    if(!buffer.empty())
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    return decodedData;
}
            
std :: vector<unsigned char> Decoder :: decodeFromInterface(InputStreamInterface& input)
{
    decodedData.clear();
    while(!input.isEndOfStream())
    {
        std :: string piece = input.readDataPiece();
        if(piece.empty())
        {
            break;
        }
        
        for(char c : piece)
        {
            if(isspace(c))
            {
                continue;
            }
            addAndCheckBuffer(c);
        }
    }
    if(!buffer.empty())
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    return decodedData;
}
        
            
            
            
            
            
            
            
            
            
            
