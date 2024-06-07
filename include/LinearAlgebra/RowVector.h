#ifndef ROWVECTOR_H
#define ROWVECTOR_H

#include "Vector.h"
#include "ColumnVector.h"
#include "Matrix.h"

#include <vector>
namespace LinearAlgebra {

  class ColumnVector; // Forward declaration for resolving circular dependency
  class Matrix;

  class RowVector: public Vector {
  public:
    RowVector(int dimension, bool randomize=false, double mean=0., double std=1.);
    RowVector(const std::vector<double>&);
    RowVector(const RowVector&);

    RowVector operator+(const RowVector&) const;
    RowVector operator-(const RowVector&) const;
    double operator*(const ColumnVector&) const;
    RowVector operator*(const Matrix&) const;
    RowVector& operator+=(const RowVector&);
    RowVector& operator-=(const RowVector&);
    RowVector& operator*=(const Matrix&);
    double dot(const RowVector&) const;
    double euclideanDistance(const RowVector&) const;
    double cosineSimilarity(const RowVector&) const;

    ColumnVector transpose() const;

    void print() override;
  };
  
}

#endif