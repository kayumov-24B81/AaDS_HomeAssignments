#include "base85.hpp"

Base85 :: Base85(): bufferSize(1024)
{
    ALPHABET = R"(!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz)";
}

std :: string Base85 :: encodeSection(std :: vector<unsigned char>& data)
{
    if (data.empty()) 
    {
        return "";
    }

    std::string encodedText;

    for (unsigned i = 0; i < data.size(); i += 4) 
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

std :: string Base85 :: encode()
{
    std :: vector<unsigned char> buffer(bufferSize);
    std :: vector<unsigned char> text;

    while(true)
    {
        std :: cin.read(reinterpret_cast<char*>(buffer.data()), bufferSize);
        std :: streamsize bytesRead = std :: cin.gcount();
        
        if(bytesRead > 0)
        {
            text.insert(text.end(), buffer.begin(), buffer.begin() + bytesRead);
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
    
    std :: string encoded = encodeSection(text);
    
    return encoded;
}
            
std :: vector<unsigned char> Base85 :: decodeSection(std :: string code)
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
    
    std::string cleaned;
    for (char c : code) {
        if (!isspace(c)) {
            cleaned += c;
        }
    }
    
    if(cleaned.size() % 5 != 0)
    {
        throw std::invalid_argument("Incorrect input data length (must be divisible by 5)");
    }
    
    std :: vector<unsigned char> text;
    
    for(unsigned i = 0; i < cleaned.size(); i += 5)
    {
        std :: string group = cleaned.substr(i, 5);
        
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
        
        text.push_back((num >> 24) & 0xFF);
        text.push_back((num >> 16) & 0xFF);
        text.push_back((num >> 8) & 0xFF);
        text.push_back(num & 0xFF);
    }
    
    return text;
}
        
std :: vector<unsigned char> Base85 :: decode()
{
    std::string encoded_data((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
    std::vector<unsigned char> decoded_data = decodeSection(encoded_data);
    return decoded_data;
}
            
    
        
            
            
            
            
            
            
            
            
            
            
