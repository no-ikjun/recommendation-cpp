#include "../../include/LinearAlgebra/Matrix.h"
#include "../../include/LinearAlgebra/Utils.h"
#include "../../include/LinearAlgebra/RowVector.h"
#include "../../include/LinearAlgebra/ColumnVector.h"

#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace LinearAlgebra{

  Matrix::Matrix() {}
  
  Matrix::Matrix(int rows, int cols, bool randomize, double mean, double std) {
    if(rows <= 0 || cols <= 0) {
      throw std::invalid_argument("Matrix can only have natural number of rows and columns");
    }
    this->rows = rows;
    this->cols = cols;
    this->data = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0.));

    if(randomize) {
      this->forEach([mean, std](double& element) {element = randn(mean, std);});
    }
  }

  Matrix::Matrix(const Matrix& other) {
    if(this->shape() != other.shape()) {
      throw std::invalid_argument("Matrix shape do not match for copy");
    }

    this->data = other.data;
  }

  std::pair<int, int> Matrix::shape() const {
    return std::make_pair(this->rows, this->cols);
  }

  double& Matrix::operator()(int row_idx, int col_idx) {
    if(row_idx < 0 || rows <= row_idx || col_idx < 0 || cols <= col_idx) {
      throw std::out_of_range("index out of bounds");
    }
    return this->data[row_idx][col_idx];
  }

  const double& Matrix::operator()(int row_idx, int col_idx) const {
    if(row_idx < 0 || rows <= row_idx || col_idx < 0 || cols <= col_idx) {
      throw std::out_of_range("index out of bounds");
    }
    return this->data[row_idx][col_idx];
  }

  // RowVector& Matrix::getRow(int index) const {
  //   if(index < 0 || rows <= index) {
  //     throw std::out_of_range("index out of bounds");
  //   }
  //   return RowVector(this->data[index]);
  // }

  Matrix Matrix::operator+(const Matrix& other) const {
    if(this->shape() != other.shape()) {
      throw std::invalid_argument("Matrix shape do not match for addition");
    }

    Matrix result(this->rows, this->cols);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        result(i, j) = (*this)(i, j) + other(i, j);
      }
    }
    return result;
  }

  Matrix Matrix::operator-(const Matrix& other) const {
    if(this->shape() != other.shape()) {
      throw std::invalid_argument("Matrix shape do not match for subtraction");
    }

    Matrix result(this->rows, this->cols);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        result(i, j) = (*this)(i, j) - other(i, j);
      }
    }
    return result;
  }

  Matrix Matrix::operator*(const Matrix& other) const {
    if(this->cols != other.shape().first) {
      throw std::invalid_argument("Matrix shape do not match for multiplication");
    }

    Matrix result(this->rows, other.shape().second);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < other.shape().second; ++j) {
        for(int k = 0; k < this->cols; ++k) {
          result(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    return result;
  }

  Matrix& Matrix::operator+=(const Matrix& other) {
    if(this->shape() != other.shape()) {
      throw std::invalid_argument("Matrix shape do not match for addition");
    }

    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        (*this)(i, j) += other(i, j);
      }
    }
    return *this;
  }

  Matrix& Matrix::operator-=(const Matrix& other) {
    if(this->shape() != other.shape()) {
      throw std::invalid_argument("Matrix shape do not match for subtraction");
    }

    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        (*this)(i, j) -= other(i, j);
      }
    }
    return *this;
  }

  Matrix& Matrix::operator*=(const Matrix& other) {
    if(this->cols != other.shape().first) {
      throw std::invalid_argument("Matrix shape do not match for multiplication");
    }

    Matrix result(this->rows, other.shape().second);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < other.shape().second; ++j) {
        for(int k = 0; k < this->cols; ++k) {
          result(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    return *this = result;
  }

  Matrix Matrix::transpose() const {
    Matrix result(this->cols, this->rows);
    for(int i = 0; i < this->rows; ++i) {
      for (int j = 0; j < this->cols; ++j) {
        result(j, i) = (*this)(i, j);
      }
    }
    return result;
  }

  void Matrix::forEach(const std::function<void(double&)>& func){
    for(std::vector<double>& row: this->data) {
      for(double& element: row) {
        func(element);
      }
    }
  }

  void Matrix::print() {
    std::cout << std::noshowpos
      << "Matrix of shape (" << this->rows << ", " << this->cols << ")"
    << std::endl;

    std::cout << "[";
    for(int i = 0; i < this->rows; ++i) {
      std::cout << (i == 0 ? "" : " ") << "[";
      for(int j = 0; j < this->cols; ++j) {
        std::cout << std::setw(2) << std::fixed << std::setprecision(2) << std::showpos 
          << (*this)(i, j)
          << (
            j == this->cols-1 
            ? (i == this->rows-1 ? "]" : "],") 
            : ", "
            );
      }
      std::cout << (i == this->rows-1 ? "]" : "") << std::endl;
    }
  }

}

