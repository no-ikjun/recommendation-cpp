#include "../../include/LinearAlgebra/Utils.h"
#include "../../include/LinearAlgebra/Vector.h"
#include "../../include/LinearAlgebra/ColumnVector.h"

#include <random>
#include <stdexcept>
#include <functional>
#include <cmath>

namespace LinearAlgebra {
  double randn(double mean, double std) {
    std::random_device randomDevice; 
    std::mt19937 generator(randomDevice());
    std::normal_distribution<double> distribution(mean, std);
    return distribution(generator);
  }

  void forInZip(Vector& vec1, Vector& vec2, const std::function<void(double&, double&)>& func) {
    if(vec1.getDimension() != vec2.getDimension()) {
      throw std::invalid_argument("Vector dimension do not match for zip operation");
    }

    for(int i = 0; i < vec1.getDimension(); ++i) {
      func(vec1(i), vec2(i));
    }
  }

  void forInZip(const Vector& vec1, Vector& vec2, const std::function<void(const double&, double&)>& func) {
    if(vec1.getDimension() != vec2.getDimension()) {
      throw std::invalid_argument("Vector dimension do not match for zip operation");
    }

    for(int i = 0; i < vec1.getDimension(); ++i) {
      func(vec1(i), vec2(i));
    }
  }

  void forInZip(Vector& vec1, const Vector& vec2, const std::function<void(double&, const double&)>& func) {
    if(vec1.getDimension() != vec2.getDimension()) {
      throw std::invalid_argument("Vector dimension do not match for zip operation");
    }

    for(int i = 0; i < vec1.getDimension(); ++i) {
      func(vec1(i), vec2(i));
    }
  }

  void forInZip(const Vector& vec1, const Vector& vec2, const std::function<void(const double&, const double&)>& func) {
    if(vec1.getDimension() != vec2.getDimension()) {
      throw std::invalid_argument("Vector dimension do not match for zip operation");
    }

    for(int i = 0; i < vec1.getDimension(); ++i) {
      func(vec1(i), vec2(i));
    }
  }

  ColumnVector oneHotEncode(int index, int dimension) {
    ColumnVector oneHotVector(dimension);
    oneHotVector(index) = 1;
    return oneHotVector;
  }

  void softmax(Vector& vector) {
    double exp_sum = 0;
    vector.forEach([&exp_sum](double& value) {
      value = std::exp(value);
      exp_sum += value;
    });
    vector.forEach([&exp_sum](double& value) {
      value /= exp_sum;
    });
  }
}