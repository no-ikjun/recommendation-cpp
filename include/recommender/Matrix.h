#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <utility>
#include <functional>

class Matrix {
public: 
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);

  std::pair<int, int> shape() const; // (rows, cols)

  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);

  Matrix transpose() const;
  void forEach(const std::function<void(double)>& func);
  void print();
  
private:
  int rows;
  int cols;
  std::vector<std::vector<double>> data;
};

#endif