#ifndef UTILS_H
#define UTILS_H

#include "Vector.h"

#include <functional>

namespace LinearAlgebra{

  double randn(double mean, double std);

  void forInZip(Vector& vec1, Vector& vec2, const std::function<void(double&, double&)>& func);
  void forInZip(const Vector& vec1, Vector& vec2, const std::function<void(const double&, double&)>& func);
  void forInZip(Vector& vec1, const Vector& vec2, const std::function<void(double&, const double&)>& func);
  void forInZip(const Vector& vec1, const Vector& vec2, const std::function<void(const double&, const double&)>& func);

}

#endif