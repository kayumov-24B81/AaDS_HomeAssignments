#ifndef LINEAR_HPP
#define LINEAR_HPP

#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void readFile(std :: vector<std :: vector<double>> &data);
void createMatrix(std :: vector<std :: vector<double>> &data, Eigen :: MatrixXd &matrix, Eigen :: VectorXd &vector);
void solveMatrix(Eigen :: MatrixXd &matrix, Eigen :: VectorXd &vector);
int foo();


class Linear
{
    private:
        std :: vector<std :: vector<double>> data;
        Eigen :: MatrixXd matrix;
        Eigen :: VectorXd vector;
        Eigen :: VectorXd answer;
    public:
        Eigen :: VectorXd getAnswer();
        void readFile(std :: string file_name);
        void fillMatrices();
        void solveEquations();
};

#endif
