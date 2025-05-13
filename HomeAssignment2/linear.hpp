#ifndef LINEAR_HPP
#define LINEAR_HPP

#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

class Linear
{
    private:
        std :: vector<std :: vector<double>> data;
        Eigen :: MatrixXd matrix;
        Eigen :: VectorXd vector;
        Eigen :: VectorXd answer;
    public:
        Eigen :: VectorXd getAnswer();
        Eigen :: MatrixXd getMatrix();
        Eigen :: VectorXd getVector();
        std :: vector<std :: vector<double>> getData(); 
        void readFile(std :: string file_name);
        void fillMatrices();
        void solveEquations();
        void writeAnswer();
};

#endif
