#include "encoder.hpp"

Encoder :: Encoder(): bufferSize(1024)
{
    ALPHABET = R"(!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz)";
}

std :: string Encoder :: encodeSection(std :: vector<unsigned char>& data)
{
    if (data.empty()) 
    {
        return "";
    }

    std::string encoded_text;

    for (size_t i = 0; i < data.size(); i += 4) 
    {
        unsigned num = 0;
        unsigned bytes_in_group = 0;

        for (unsigned j = 0; j < 4; ++j) 
        {
            unsigned char byte = (i + j < data.size()) ? data[i + j] : 0;
            num = (num << 8) | byte;
            
            if (i + j < data.size()) 
            {
                ++bytes_in_group;
            }
        }

        if (num == 0 && bytes_in_group == 4) 
        {
            encoded_text += 'z';
            continue;
        }

        unsigned char values[5];
        
        for (int j = 4; j >= 0; --j) 
        {
            values[j] = num % 85;
            num /= 85;
        }

        if (bytes_in_group == 4) 
        {
            for (unsigned j = 0; j < 5; ++j)
            {
                encoded_text += ALPHABET[values[j]];
            }
        } 
        else 
        {
            for (unsigned j = 0; j < bytes_in_group + 1; ++j)
            {
                encoded_text += ALPHABET[values[j]];
            }
        }
    }

    return encoded_text;
}

std :: string Encoder :: encode()
{
    std :: vector<unsigned char> buffer(bufferSize);
    std :: vector<unsigned char> code;

    while(true)
    {
        std :: cin.read(reinterpret_cast<char*>(buffer.data()), bufferSize);
        std :: streamsize bytesRead = std :: cin.gcount();
        
        if(bytesRead > 0)
        {
            code.insert(code.end(), buffer.begin(), buffer.begin() + bytesRead);
        }
        
        if(std :: cin.eof())
        {
            break;
        }
        
        if(!std :: cin)
        {
            throw std::invalid_argument("Data reading error!");
        }
    }
    
    std :: string encoded = encodeSection(code);
    
    return encoded;
}
            
            
            
            
            
            
            
            
            
            
            
            
            
            
