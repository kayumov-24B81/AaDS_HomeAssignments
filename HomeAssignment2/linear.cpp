#include "linear.hpp"

int foo()
{
    return 0;
}

// .csv file reading
void readFile(std :: vector<std :: vector<float>> &data)
{
    std :: ifstream file;
    std :: string line;
    
    file.open("matrix.csv");
    while(std :: getline(file, line))
    {
        std :: stringstream line_stream(line);
        std :: vector<float> row;
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
Eigen :: MatrixXf createMatrix(std :: vector<std :: vector<float>> &data)
{
    unsigned rows = data.size();
    unsigned columns = data[0].size();
    
    Eigen :: MatrixXf matrix(rows, columns);
    
    for(unsigned i = 0; i < rows; ++i)
    {
        for(unsigned j = 0; j < columns; ++j)
        {
            matrix(i, j) = data[i][j];
        }
    }
    
    return matrix;
}







