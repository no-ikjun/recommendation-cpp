#include "../include/recommender/Matrix.h"

#include <iostream>

int main() {
  Matrix m1(2, 3);
  m1(1, 2) = 3;
  m1.print();

  Matrix m2(3, 3);
  m2(2, 1) = 3;
  m2.print();

  Matrix m3 = m1 * m2;
  m3.print();
}