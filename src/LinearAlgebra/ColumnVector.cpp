#include "../../include/LinearAlgebra/Vector.h"
#include "../../include/LinearAlgebra/ColumnVector.h"
#include "../../include/LinearAlgebra/RowVector.h"
#include "../../include/LinearAlgebra/Utils.h"

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace LinearAlgebra;

ColumnVector::ColumnVector(
  int dimension, bool randomize, double mean, double std
): Vector(dimension, randomize, mean, std) {}

ColumnVector::ColumnVector(const std::vector<double>& other): Vector(other) {}

ColumnVector::ColumnVector(const ColumnVector& other): Vector(other.data) {}

ColumnVector ColumnVector::operator+(const ColumnVector& other) const {
  ColumnVector result = *this;
  forInZip(result, other, [] (double& element1, const double& element2) {
    element1 += element2;
  });
  return result;
}

ColumnVector ColumnVector::operator-(const ColumnVector& other) const {
  ColumnVector result = *this;
  forInZip(result, other, [] (double& element1, const double& element2) {
    element1 -= element2;
  });
  return result;
}

Matrix ColumnVector::operator*(const RowVector& other) const {
  Matrix result(this->getDimension(), other.getDimension());
  for(int i = 0; i < this->getDimension(); ++i) {
    for(int j = 0; j < other.getDimension(); ++j) {
      result(i, j) = (*this)(i) * other(j);
    }
  }
  return result;
}

ColumnVector ColumnVector::operator*(const double& scalar) const {
  ColumnVector result = *this;
  result.forEach([scalar] (double& element) {
    element *= scalar;
  });
  return result;
}

ColumnVector ColumnVector::operator/(const double& scalar) const {
  ColumnVector result = *this;
  result.forEach([scalar] (double& element) {
    element /= scalar;
  });
  return result;
}

ColumnVector& ColumnVector::operator+=(const ColumnVector& other) {
  forInZip(*this, other, [] (double& element1, const double& element2) {
    element1 += element2;
  });
  return *this;
}

ColumnVector& ColumnVector::operator-=(const ColumnVector& other) {
  forInZip(*this, other, [] (double& element1, const double& element2) {
    element1 -= element2;
  });
  return *this;
}

ColumnVector& ColumnVector::operator*=(const double& scalar) {
  this->forEach([scalar] (double& element) {
    element *= scalar;
  });
  return *this;
}

ColumnVector& ColumnVector::operator/=(const double& scalar) {
  this->forEach([scalar] (double& element) {
    element /= scalar;
  });
  return *this;
}

double ColumnVector::dot(const ColumnVector& other) const {
  double result = 0;
  forInZip(*this, other, [&result] (const double& element1, const double& element2) {
    result += element1 * element2;
  });
  return result;
}

double ColumnVector::euclideanDistance(const ColumnVector& other) const {
  double result = 0;
  forInZip(*this, other, [&result] (const double& element1, const double& element2) {
    result += (element1 - element2) * (element1 - element2);
  });
  result = std::sqrt(result);
  return result;
}

double ColumnVector::cosineSimilarity(const ColumnVector& other) const {
  if(this->norm() == 0 || other.norm() == 0) {
    return 0;
  }
  double result = this->dot(other) / (this->norm() * other.norm());
  return result;
}

RowVector ColumnVector::transpose() const {
  RowVector result(this->getDimension());
  forInZip(*this, result, [] (const double& element1, double& element2) {
    element2 = element1;
  });
  return result;
}

void ColumnVector::print(bool compact) const {
  std::cout << std::noshowpos
    << "Column vector of dimension " << this->getDimension()
  << std::endl;

  if(!compact) {
    std::cout << "[";
    for(int i = 0; i < this->getDimension(); ++i) {
      std::cout
        << (i == 0 ? "": " ")
        << std::setw(2) << std::fixed << std::setprecision(2) << std::showpos 
        << (*this)(i)
        << (i == this->getDimension() - 1 ? "]": ", ")
      << std::endl;
    }
  }
}

void ColumnVector::serialize(std::ostream& os) const {
  os << this->getDimension() << " ";
  for(int i = 0; i < this->getDimension(); ++i) {
    os << (*this)(i) << " ";
  }
}

void ColumnVector::deserialize(std::istream& is) {
  int dimension;
  is >> dimension;
  this->data.resize(dimension);
  for(int i = 0; i < this->getDimension(); ++i) {
    is >> (*this)(i);
  }
}