#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

#include <vector>
#include <functional>

namespace LinearAlgebra {

  class Vector {
  public: 
    Vector(int dimension, bool randomize, double mean, double std);
    Vector(const Vector&);

    int getDimension() const;

    double& operator()(int index);
    const double& operator()(int index) const;

    double norm() const;
    void normalize();

    void forEach(const std::function<void(double&)>& func);
    void forEach(const std::function<void(const double&)>& func);

    virtual void print() = 0;
  
  private:
    std::vector<double> data;
  };

}

#endif