#include "linear.hpp"

int main()
{
    Linear linear;
    
    linear.readFile("matrix.csv");
    linear.fillMatrices();
    linear.solveEquations();
    
    std :: cout << linear.getAnswer() << std :: endl;
}
