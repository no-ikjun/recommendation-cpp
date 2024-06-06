#include "../include/LinearAlgebra/Matrix.h"

#include <iostream>

using namespace LinearAlgebra;

int main() {
  Matrix m1(2, 3, true);
  m1(1, 2) = 3;
  m1.print();

  Matrix m2(2, 3);
  m2(0, 1) = 3;
  m2.print();

  Matrix m3 = m1 * m2.transpose();
  m3.print();
}