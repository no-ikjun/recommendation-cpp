#include "../include/LinearAlgebra/Matrix.h"
#include "../include/LinearAlgebra/Vector.h"
#include "../include/LinearAlgebra/ColumnVector.h"
#include "../include/LinearAlgebra/RowVector.h"

#include <iostream>

using namespace LinearAlgebra;

int main() {
  // Test ColumnVector
  std::cout << "Testing ColumnVector:" << std::endl;
  ColumnVector cv1(3, true);
  ColumnVector cv2(3, true);
  std::cout << "cv1: " << std::endl;
  cv1.print();
  std::cout << "cv2: " << std::endl;
  cv2.print();

  std::cout << "cv1 + cv2: " << std::endl;
  (cv1 + cv2).print();
  std::cout << "cv1 - cv2: " << std::endl;
  (cv1 - cv2).print();
  std::cout << "cv1 dot cv2: " << cv1.dot(cv2) << std::endl;
  std::cout << "Euclidean distance between cv1 and cv2: " << cv1.euclideanDistance(cv2) << std::endl;

  // Test RowVector
  std::cout << "\nTesting RowVector:" << std::endl;
  RowVector rv1(3, true);
  RowVector rv2(3, true);
  std::cout << "rv1: " << std::endl;
  rv1.print();
  std::cout << "rv2: " << std::endl;
  rv2.print();

  std::cout << "rv1 + rv2: " << std::endl;
  (rv1 + rv2).print();
  std::cout << "rv1 - rv2: " << std::endl;
  (rv1 - rv2).print();
  std::cout << "rv1 dot rv2: " << rv1.dot(rv2) << std::endl;
  std::cout << "Euclidean distance between rv1 and rv2: " << rv1.euclideanDistance(rv2) << std::endl;

  return 0;
}