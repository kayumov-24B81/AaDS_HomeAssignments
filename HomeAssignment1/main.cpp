#include "encoder.hpp"

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
            std :: cerr << "Use adcii85 wthi -d or -e flags" << std :: endl;
            return 1;
        }
    }

    Encoder encoder;
    
    if(encodingMode)
    {
        std :: cout << "Write your text(Ctrl + D for end of text):" << std :: endl;
        std :: string encoded;
    
        try
        {
            encoded = encoder.encode();
        }
    
        catch (const std::exception& e) 
        {
            std :: cerr << "Ошибка: " << e.what() << std :: endl;
            return 1;
        }
    
        std :: cout << std :: endl << encoded << std :: endl;
    
        return 0;
    }
}
