#include "../../include/LinearAlgebra/Vector.h"
#include "../../include/LinearAlgebra/Utils.h"

#include <stdexcept>
#include <cmath>
#include <vector>

using namespace LinearAlgebra;

Vector::Vector(int dimension, bool randomize=false, double mean=0., double std=1.) {
  this->data = std::vector<double>(dimension);

  if(randomize) {
    this->forEach([&mean, &std](double& value) {
      value = randn(mean, std);
    });
  }
}

Vector::Vector(const std::vector<double>& other) {
  this->data = other;
}

int Vector::getDimension() const {
  return this->data.size();
}

double& Vector::operator()(int index) {
  if(index < 0 || this->getDimension() <= index) {
    throw std::out_of_range("index out of bounds");
  }
  return this->data[index];
}

const double& Vector::operator()(int index) const {
  if(index < 0 || this->getDimension() <= index) {
    throw std::out_of_range("index out of bounds");
  }
  return this->data[index];
}

double Vector::norm() const {
  double result = 0;
  for(double element: this->data) {
    result += element * element;
  }
  result = std::sqrt(result);
  return result;
}

void Vector::normalize() {
  double norm = this->norm();
  this->forEach(
    [&norm](double& element) {
      element / norm;
    }
  );
}

void Vector::forEach(const std::function<void(double&)>& func) {
  for(double& element: this->data) {
    func(element);
  }
};

void Vector::forEach(const std::function<void(const double&)>& func) {
  for(const double& element: this->data) {
    func(element);
  }
};