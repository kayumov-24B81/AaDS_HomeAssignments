#include "linear.hpp"

int foo()
{
    return 0;
}

Eigen :: VectorXd Linear :: getAnswer()
{
    return answer;
}

void Linear :: readFile(std :: string file_name)
{
    std :: ifstream file;
    std :: string line;
    
    file.open(file_name);
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

void Linear :: fillMatrices()
{
    matrix.resize(data.size(), data[0].size() - 1);
    vector.resize(data.size());
    
    for(unsigned i = 0; i < data.size(); ++i)
    {
        for(unsigned j = 0; j < data[0].size() - 1; ++j)
        {
            matrix(i, j) = data[i][j];
        }
        vector(i) = data[i][data[0].size() - 1];
    }
}

void Linear :: solveEquations()
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
            throw std :: runtime_error("Singular matrix. No solutions");
            return;
        }
        
        
        for(int j = i + 1; j < n; ++j)
        {
            double factor = matrix(j, i) / matrix(i, i);
            matrix.row(j) -= factor * matrix.row(i);
            vector(j) -= factor * vector(i);
        }
    }
     
    answer = matrix.triangularView<Eigen :: Upper>().solve(vector);
}
        
    
    
