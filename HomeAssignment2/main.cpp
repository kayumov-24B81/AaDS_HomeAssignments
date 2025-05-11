#include "linear.hpp"

int main()
{
    std :: vector<std :: vector<float>> data;
    readFile(data);
    std :: cout << createMatrix(data) << std :: endl;
}
