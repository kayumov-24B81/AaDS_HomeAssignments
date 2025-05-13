#include <gtest/gtest.h>
#include <random>
#include "linear.hpp"

TEST(Lineartest, readFile_test)
{
    Linear linear;
    
    linear.readFile("matrix.csv");
    std :: vector<std :: vector<double>> data;
    data.push_back({3,2,-1,1});
    data.push_back({2,-2,4,-2});
    data.push_back({-1,0.5,-1,0});
    
    EXPECT_EQ(data, linear.getData());
}
    
TEST(Lineartest, fillMatrices_test)
{
    Linear linear;
    
    linear.readFile("matrix.csv");
    linear.fillMatrices();
    
    Eigen :: Matrix3d matrix;
    Eigen :: Vector3d vector;
    
    matrix << 3, 2, -1, 
          2, -2, 4, 
          -1, 0.5, -1;
    
    vector << 1, -2, 0;
    
    EXPECT_TRUE(matrix.isApprox(linear.getMatrix(), 1e-12));
    EXPECT_TRUE(vector.isApprox(linear.getVector(), 1e-12));
}

TEST(Lineartest, solveEquations_test)
{
    Linear linear;
    
    linear.readFile("matrix.csv");
    linear.fillMatrices();
    linear.solveEquations();
    
    Eigen :: Vector3d vector(1, -2, -2);
    
    EXPECT_TRUE(vector.isApprox(linear.getAnswer(), 1e-12));
}

TEST(Lineartest, writeAnswer_test)
{
    Linear linear;
    
    linear.readFile("matrix.csv");
    linear.fillMatrices();
    linear.solveEquations();
    linear.writeAnswer();
    
    Eigen :: Vector3d vector;
    
    std :: ifstream file;
    file.open("answer.csv");
    
    std :: string line;
    std :: getline(file, line);
    
    std :: stringstream line_stream(line);
    std :: string cell;
    
    for(unsigned i = 0; i < 3; ++i)
    {
        std :: getline(line_stream, cell, ',');
        vector(i) = std :: stod(cell);
    }
    
    EXPECT_TRUE(vector.isApprox(linear.getAnswer(), 1e-12));
}

TEST(Lineartest, random_test)
{
    std :: srand(193);
    
    unsigned size = (rand() % 100) + 10;
    
    Eigen :: VectorXd answer = Eigen::VectorXd::Random(size);
    Eigen :: MatrixXd matrix = Eigen::MatrixXd::Random(size, size);
    
    matrix = matrix * matrix.transpose();
    matrix.diagonal().array() += 10.0;
    
    Eigen :: VectorXd vector = matrix * answer;
    
    std :: ofstream file;
    file.open("test.csv");
    
    if(file.is_open())
    {
        Eigen :: MatrixXd full_matrix(size, size + 1);
        full_matrix << matrix, vector;
        Eigen :: IOFormat full_format(15, Eigen::DontAlignCols, ",", "\n");
        file << full_matrix.format(full_format);
        file.close();
    }
    else
    {
        throw std :: runtime_error("Unable to open file for tests");
    }
    
    Linear linear;
    
    linear.readFile("test.csv");
    linear.fillMatrices();
    linear.solveEquations();
    
    EXPECT_TRUE(answer.isApprox(linear.getAnswer(), 1e-6));
}

    

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
