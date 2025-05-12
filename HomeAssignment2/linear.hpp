#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

void readFile(std :: vector<std :: vector<double>> &data);
void createMatrix(std :: vector<std :: vector<double>> &data, Eigen :: MatrixXd &matrix, Eigen :: VectorXd &vector);
void solveMatrix(Eigen :: MatrixXd &matrix, Eigen :: VectorXd &vector);
int foo();
