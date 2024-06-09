#ifndef COLUMNVECTOR_H
#define COLUMNVECTOR_H

#include "Vector.h"
#include "RowVector.h"
#include "Matrix.h"

namespace LinearAlgebra {

  class RowVector; // Forward declaration for resolving circular dependency
  class Matrix; // Forward declaration for resolving circular dependency

  class ColumnVector: public Vector {
  public:
    ColumnVector(int dimension, bool randomize=false, double mean=0., double std=1.);
    ColumnVector(const std::vector<double>&);
    ColumnVector(const ColumnVector&);
  
    ColumnVector operator+(const ColumnVector&) const;
    ColumnVector operator-(const ColumnVector&) const;
    Matrix operator*(const RowVector&) const;
    ColumnVector operator*(const double&) const;
    ColumnVector operator/(const double&) const;
    ColumnVector& operator+=(const ColumnVector&);
    ColumnVector& operator-=(const ColumnVector&);
    ColumnVector& operator*=(const double&);
    ColumnVector& operator/=(const double&);
    double dot(const ColumnVector&) const;
    double euclideanDistance(const ColumnVector&) const;
    double cosineSimilarity(const ColumnVector&) const;
    RowVector transpose() const;

    void print(bool compact=false) const override;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
  };
  
}

#endif