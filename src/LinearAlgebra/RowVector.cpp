#include "../../include/LinearAlgebra/Vector.h"
#include "../../include/LinearAlgebra/RowVector.h"
#include "../../include/LinearAlgebra/RowVector.h"
#include "../../include/LinearAlgebra/Utils.h"

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace LinearAlgebra;

RowVector::RowVector(
  int dimension, bool randomize, double mean, double std
): Vector(dimension, randomize, mean, std) {}

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
  double result = other.dot(this->transpose());
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

void RowVector::print() {
  std::cout << std::noshowpos
    << "Row vector of dimension " << this->getDimension()
  << std::endl;

  std::cout << "[";
  for(int i = 0; i < this->getDimension(); ++i) {
    std::cout << std::setw(2) << std::fixed << std::setprecision(2) << std::showpos 
      << (*this)(i)
      << (i == this->getDimension() - 1 ? "]": ", ");
  }
  std::cout << std::endl;
}