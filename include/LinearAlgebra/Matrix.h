#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

#include <vector>
#include <utility>
#include <functional>

namespace LinearAlgebra{

  class ColumnVector;
  class RowVector;

  class Matrix {
  public: 
    Matrix();
    Matrix(int rows, int cols, bool randomize=false, double mean=0., double std=1.);
    Matrix(const Matrix&);

    std::pair<int, int> shape() const; // (rows, cols)

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;

    RowVector getRow(int index) const;
    ColumnVector getColumn(int index) const;

    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    ColumnVector operator*(const ColumnVector&) const;
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&);

    Matrix transpose() const;
    void forEach(const std::function<void(double&)>& func);
    void print();
    
  private:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;
  };

}

#endif