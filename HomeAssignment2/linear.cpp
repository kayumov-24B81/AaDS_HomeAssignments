#include "linear.hpp"

int foo()
{
    return 0;
}

// .csv file reading
void readFile(std :: vector<std :: vector<double>> &data)
{
    std :: ifstream file;
    std :: string line;
    
    file.open("matrix.csv");
    while(std :: getline(file, line))
    {
        std :: stringstream line_stream(line);
        std :: vector<double> row;
        std :: string cell;
        
        while(std :: getline(line_stream, cell, ','))
        {
            row.push_back(std :: stof(cell));
        }
        
        if(!row.empty())
        {
            data.push_back(row);
        }
    }
}

// matrix creation
void createMatrix(std :: vector<std :: vector<double>> &data, 
                  Eigen :: MatrixXd &matrix,
                  Eigen :: VectorXd &vector)
{
    for(unsigned i = 0; i < data.size(); ++i)
    {
        for(unsigned j = 0; j < data[0].size() - 1; ++j)
        {
            matrix(i, j) = data[i][j];
        }
        vector(i) = data[i][data[0].size() - 1];
    }
}

// solve matrix
void solveMatrix(Eigen :: MatrixXd &matrix, Eigen :: VectorXd &vector)
{
    int n = matrix.rows();
    
    for(int i = 0; i < n; ++i)
    {
        int max_row = i;
        for(int j = i + 1; j < n; ++j)
        {
            if(abs(matrix(j, i)) > abs(matrix(max_row, i)))
            {
                max_row = j;
            }
        }
        matrix.row(i).swap(matrix.row(max_row));
        std::swap(vector(i), vector(max_row));
        
        if(abs(matrix(i, i)) < 1e-12)
        {
            std :: cerr << ("Singular matrix. No solutions") << std :: endl;
            return;
        }
        
        
        for(int j = i + 1; j < n; ++j)
        {
            double factor = matrix(j, i) / matrix(i, i);
            matrix.row(j) -= factor * matrix.row(i);
            vector(j) -= factor * vector(i);
        }
    }
     
    std :: cout << matrix.triangularView<Eigen :: Upper>().solve(vector) << std :: endl;
}
   
        
    
    
