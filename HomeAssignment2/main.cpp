#include "linear.hpp"

int main()
{
    std :: vector<std :: vector<double>> data;
    readFile(data);
    
    unsigned rows = data.size();
    unsigned columns = data[0].size() - 1;
    Eigen :: MatrixXd matrix(rows, columns);
    Eigen :: VectorXd vector(rows);
  
    createMatrix(data, matrix, vector);
    
    std :: cout << "matrix\n" << matrix << std :: endl;
    std :: cout << "vector\n" << vector << std :: endl;
    
    solveMatrix(matrix, vector);
}
