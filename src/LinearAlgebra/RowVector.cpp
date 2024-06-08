#include "../../include/LinearAlgebra/Vector.h"
#include "../../include/LinearAlgebra/RowVector.h"
#include "../../include/LinearAlgebra/Utils.h"

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace LinearAlgebra;

RowVector::RowVector(
  int dimension, bool randomize, double mean, double std
): Vector(dimension, randomize, mean, std) {}

RowVector::RowVector(const std::vector<double>& other): Vector(other) {}

RowVector::RowVector(const RowVector& other): Vector(other.data) {}

RowVector RowVector::operator+(const RowVector& other) const {
  RowVector result = *this;
  forInZip(result, other, [] (double& element1, const double& element2) {
    element1 += element2;
  });
  return result;
}

RowVector RowVector::operator-(const RowVector& other) const {
  RowVector result = *this;
  forInZip(result, other, [] (double& element1, const double& element2) {
    element1 -= element2;
  });
  return result;
}

double RowVector::operator*(const ColumnVector& other) const {
  double result = this->dot(other.transpose());
  return result;
}

RowVector RowVector::operator*(const Matrix& other) const {
  if(this->getDimension() != other.shape().first) {
    throw std::invalid_argument("Shape mismatch for row vector and matrix multiplication");
  }
  RowVector result(other.shape().second);
  for(int i = 0; i < other.shape().second; ++i) {
    result(i) = (*this) * other.getColumn(i);
  }
  return result;
}

RowVector RowVector::operator*(const double& scalar) const {
  RowVector result = *this;
  result.forEach([scalar] (double& element) {
    element *= scalar;
  });
  return result;
}

RowVector RowVector::operator/(const double& scalar) const {
  RowVector result = *this;
  result.forEach([scalar] (double& element) {
    element /= scalar;
  });
  return result;
}

RowVector& RowVector::operator+=(const RowVector& other) {
  forInZip(*this, other, [] (double& element1, const double& element2) {
    element1 += element2;
  });
  return *this;
}

RowVector& RowVector::operator-=(const RowVector& other) {
  forInZip(*this, other, [] (double& element1, const double& element2) {
    element1 -= element2;
  });
  return *this;
}

RowVector& RowVector::operator*=(const Matrix& other) {
  if(this->getDimension() != other.shape().first) {
    throw std::invalid_argument("Shape mismatch for row vector and matrix multiplication");
  }
  for(int i = 0; i < other.shape().second; ++i) {
    (*this)(i) = (*this) * other.getColumn(i);
  }
  return *this;
}

RowVector& RowVector::operator*=(const double& scalar) {
  this->forEach([scalar] (double& element) {
    element *= scalar;
  });
  return *this;
}

RowVector& RowVector::operator/=(const double& scalar) {
  this->forEach([scalar] (double& element) {
    element /= scalar;
  });
  return *this;
}

double RowVector::dot(const RowVector& other) const {
  double result = 0;
  forInZip(*this, other, [&result] (const double& element1, const double& element2) {
    result += element1 * element2;
  });
  return result;
}

double RowVector::euclideanDistance(const RowVector& other) const {
  double result = 0;
  forInZip(*this, other, [&result] (const double& element1, const double& element2) {
    result += (element1 - element2) * (element1 - element2);
  });
  result = std::sqrt(result);
  return result;
}

double RowVector::cosineSimilarity(const RowVector& other) const {
  double result = this->dot(other) / (this->norm() * other.norm());
  return result;
}

ColumnVector RowVector::transpose() const {
  ColumnVector result(this->getDimension());
  forInZip(*this, result, [] (const double& element1, double& element2) {
    element2 = element1;
  });
  return result;
}

void RowVector::print(bool compact) const {
  std::cout << std::noshowpos
    << "Row vector of dimension " << this->getDimension()
  << std::endl;

  if(!compact) {
    std::cout << "[";
    for(int i = 0; i < this->getDimension(); ++i) {
      std::cout << std::setw(2) << std::fixed << std::setprecision(2) << std::showpos 
        << (*this)(i)
        << (i == this->getDimension() - 1 ? "]": ", ");
    }
    std::cout << std::endl;
  }
}