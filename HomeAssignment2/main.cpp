#include "linear.hpp"

int main(int argc, char* argv[])
{
    Linear linear;
    if(argc > 1)
    {
        std :: string arg(argv[1]);
        linear.readFile(arg);
    }
    else
    {
        linear.readFile("matrix.csv");
    }
    
    linear.fillMatrices();
    
    try
    {
        linear.solveEquations();
    }
    catch (const std::exception& e) 
    {
        std :: cerr << "\nError: " << e.what() << std :: endl;
        return 1;
    }
    
    linear.writeAnswer();
}
