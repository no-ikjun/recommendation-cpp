#include "../../include/LinearAlgebra/Matrix.h"
#include "../../include/LinearAlgebra/ColumnVector.h"
#include "../../include/LinearAlgebra/Utils.h"

#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <system_error>
#include <fstream>
#include <string>
#include <ios>

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

  Matrix::Matrix(const Matrix& other): rows(other.rows), cols(other.cols), data(other.data) {}

  std::pair<int, int> Matrix::shape() const {
    return std::make_pair(this->rows, this->cols);
  }

  double& Matrix::operator()(int row_idx, int col_idx) {
    if(row_idx < 0 || this->rows <= row_idx || col_idx < 0 || this->cols <= col_idx) {
      throw std::out_of_range("index out of bounds");
    }
    return this->data[row_idx][col_idx];
  }

  const double& Matrix::operator()(int row_idx, int col_idx) const {
    if(row_idx < 0 || this->rows <= row_idx || col_idx < 0 || this->cols <= col_idx) {
      throw std::out_of_range("index out of bounds");
    }
    return this->data[row_idx][col_idx];
  }

  RowVector Matrix::getRow(int index) const {
    if(index < 0 || this->rows <= index) {
      throw std::out_of_range("index out of bounds");
    }
    RowVector rowVector(this->data[index]);
    return rowVector;
  }

  ColumnVector Matrix::getColumn(int index) const {
    if(index < 0 || this->cols <= index) {
      throw std::out_of_range("index out of bounds");
    }
    ColumnVector columnVector(this->rows);
    for(int i = 0; i < this->rows; ++i) {
      columnVector(i) = this->data[i][index];
    }
    return columnVector;
  }

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

  ColumnVector Matrix::operator*(const ColumnVector& vec) const {
    if(this->cols != vec.getDimension()) {
      throw std::invalid_argument("Matrix shape do not match for multiplication with ColumnVector");
    }

    ColumnVector result(this->rows);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        result(i) += (*this)(i, j) * vec(j);
      }
    }
    return result;
  }

  Matrix Matrix::operator*(const double& scalar) const {
    Matrix result(this->rows, this->cols);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        result(i, j) = (*this)(i, j) * scalar;
      }
    }
    return result;
  }

  Matrix Matrix::operator/(const double& scalar) const {
    if(scalar == 0) {
      throw std::invalid_argument("Division by zero");
    }

    Matrix result(this->rows, this->cols);
    for(int i = 0; i < this->rows; ++i){
      for(int j = 0; j < this->cols; ++j) {
        result(i, j) = (*this)(i, j) / scalar;
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

  Matrix& Matrix::operator*=(const double& scalar) {
    this->forEach([scalar](double& element) {element *= scalar;});
    return *this;
  }

  Matrix& Matrix::operator/=(const double& scalar) {
    if(scalar == 0) {
      throw std::invalid_argument("Division by zero");
    }

    this->forEach([scalar](double& element) {element /= scalar;});
    return *this;
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

  void Matrix::print(bool compact) const {
    std::cout << std::noshowpos
      << "Matrix of shape (" << this->rows << ", " << this->cols << ")"
    << std::endl;

    if(!compact) {
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

  void Matrix::saveAs(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file for writing");
    }

    file.write(reinterpret_cast<const char*>(&this->rows), sizeof(int));
    file.write(reinterpret_cast<const char*>(&this->cols), sizeof(int));

    for (const std::vector<double>& row : this->data) {
      file.write(reinterpret_cast<const char*>(row.data()), sizeof(double) * this->cols);
    }

    file.close();
  }

  void Matrix::loadFrom(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file for reading");
    }

    int rows, cols;
    file.read(reinterpret_cast<char*>(&rows), sizeof(int));
    file.read(reinterpret_cast<char*>(&cols), sizeof(int));

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
      std::vector<double> row(cols);
      file.read(reinterpret_cast<char*>(row.data()), sizeof(double) * cols);
      result.data[i] = row;
    }

    file.close();

    *this = result;
  }

}

