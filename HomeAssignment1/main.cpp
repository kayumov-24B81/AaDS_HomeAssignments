#include "base85.hpp"

int main(int argc, char* argv[])
{
    bool encodingMode = true;
    if(argc > 1)
    {
        std :: string arg(argv[1]);
        if(arg == "-d")
        {
            encodingMode = false;
        }
        else if(arg != "-e")
        {
            std :: cerr << "Use ascii85 wthi -d or -e flags" << std :: endl;
            return 1;
        }
    }

    Base85 coder;
    
    if(encodingMode)
    {
        std :: cout << "Write text you need to encode(Ctrl + D for end of text):" << std :: endl;
        std :: string encoded;
        try
        {
            encoded = coder.encodeStream();
        }
    
        catch (const std::exception& e) 
        {
            std :: cout << std :: endl;
            std :: cerr << "Error: " << e.what() << std :: endl;
            return 1;
        }
    
        std :: cout << std :: endl << encoded << std :: endl;
    
        return 0;
    }
    else
    {
        std :: cout << "Write text you need to decode(Ctrl + D for end of text):" << std :: endl;
        std :: vector<unsigned char> decoded;
    
        try
        {
            decoded = coder.decodeStream();
        }
    
        catch (const std::exception& e) 
        {
            std :: cout << std :: endl;
            std :: cerr << "Error: " << e.what() << std :: endl;
            return 1;
        }

        std :: cout << std :: endl;
        
        for(unsigned char byte : decoded)
        {
            std :: cout << byte;
        }
        
        return 0;
    } 
}
