#include "../include/LinearAlgebra/Matrix.h"
#include "../include/LinearAlgebra/Vector.h"
#include "../include/LinearAlgebra/ColumnVector.h"
#include "../include/LinearAlgebra/RowVector.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace LinearAlgebra;

int main() {
  // Test ColumnVector
  std::cout << "Testing ColumnVector:" << std::endl;
  ColumnVector cv1(3, true);
  ColumnVector cv2(3, true);
  ColumnVector cv3(cv1);  // Test copy constructor

  std::cout << "cv1: " << std::endl;
  cv1.print();
  std::cout << std::endl;

  std::cout << "cv2: " << std::endl;
  cv2.print();
  std::cout << std::endl;

  std::cout << "cv1 + cv2: " << std::endl;
  (cv1 + cv2).print();
  std::cout << std::endl;

  std::cout << "cv1 - cv2: " << std::endl;
  (cv1 - cv2).print();
  std::cout << std::endl;

  std::cout << "cv1 dot cv2: " << cv1.dot(cv2) << std::endl;
  std::cout << std::endl;
  
  std::cout << "Euclidean distance between cv1 and cv2: " 
    << cv1.euclideanDistance(cv2) << std::endl;
  std::cout << std::endl;

  std::cout << "Cosine similarity between cv1 and cv2: " 
    << cv1.cosineSimilarity(cv2) << std::endl;
  std::cout << std::endl;

  cv1 += cv2;
  std::cout << "cv1 after += cv2: " << std::endl;
  cv1.print();
  std::cout << std::endl;

  cv1 -= cv2;
  std::cout << "cv1 after -= cv2: " << std::endl;
  cv1.print();
  std::cout << std::endl;

  std::cout << "Transpose of cv1: " << std::endl;
  cv1.transpose().print();
  std::cout << std::endl;

  cv1.normalize();
  std::cout << "Normalized cv1: " << std::endl;
  cv1.print();
  std::cout << std::endl;


  // Test RowVector
  std::cout << "\nTesting RowVector:" << std::endl;
  RowVector rv1(3, true);
  RowVector rv2(3, true);
  RowVector rv3(rv1);  // Test copy constructor

  std::cout << "rv1: " << std::endl;
  rv1.print();
  std::cout << std::endl;

  std::cout << "rv2: " << std::endl;
  rv2.print();
  std::cout << std::endl;

  std::cout << "rv1 + rv2: " << std::endl;
  (rv1 + rv2).print();
  std::cout << std::endl;

  std::cout << "rv1 - rv2: " << std::endl;
  (rv1 - rv2).print();
  std::cout << std::endl;

  std::cout << "rv1 dot rv2: " << rv1.dot(rv2) << std::endl;
  std::cout << std::endl;

  std::cout << "Euclidean distance between rv1 and rv2: " 
    << rv1.euclideanDistance(rv2) << std::endl;
  std::cout << std::endl;

  std::cout << "Cosine similarity between rv1 and rv2: " 
    << rv1.cosineSimilarity(rv2) << std::endl;
  std::cout << std::endl;

  rv1 += rv2;
  std::cout << "rv1 after += rv2: " << std::endl;
  rv1.print();
  std::cout << std::endl;

  rv1 -= rv2;
  std::cout << "rv1 after -= rv2: " << std::endl;
  rv1.print();
  std::cout << std::endl;

  std::cout << "Transpose of rv1: " << std::endl;
  rv1.transpose().print();
  std::cout << std::endl;

  rv1.normalize();
  std::cout << "Normalized rv1: " << std::endl;
  rv1.print();
  std::cout << std::endl;

  // Test Matrix
  std::cout << "\nTesting Matrix:" << std::endl;
  Matrix m1(3, 3, true);
  Matrix m2(3, 3, true);
  Matrix m3(m1);  // Test copy constructor

  std::cout << "m1: " << std::endl;
  m1.print();
  std::cout << std::endl;

  std::cout << "m2: " << std::endl;
  m2.print();
  std::cout << std::endl;

  std::cout << "m1 + m2: " << std::endl;
  (m1 + m2).print();
  std::cout << std::endl;

  std::cout << "m1 - m2: " << std::endl;
  (m1 - m2).print();
  std::cout << std::endl;

  std::cout << "m1 * m2: " << std::endl;
  (m1 * m2).print();
  std::cout << std::endl;

  m1 += m2;
  std::cout << "m1 after += m2: " << std::endl;
  m1.print();
  std::cout << std::endl;

  m1 -= m2;
  std::cout << "m1 after -= m2: " << std::endl;
  m1.print();
  std::cout << std::endl;

  std::cout << "Transpose of m1: " << std::endl;
  m1.transpose().print();
  std::cout << std::endl;


  // Test Matrix-vector multiplication
  std::cout << "\nTesting Matrix-vector multiplication:" << std::endl;

  std::cout << "m1 * cv1: " << std::endl;
  (m1 * cv1).print();
  std::cout << std::endl;

  std::cout << "rv1 * m1: " << std::endl;
  (rv1 * m1).print();
  std::cout << std::endl;

  std::cout << "rv1 * cv1: " << std::endl;
  std::cout << rv1 * cv1 << std::endl;
  std::cout << std::endl;

  std::cout << "cv1 * rv1: " << std::endl;
  (cv1 * rv1).print();
  std::cout << std::endl;
  

  // Test forEach method
  std::cout << "\nTesting forEach method:" << std::endl;

  cv1.forEach([](double& val) { val *= 2; });
  std::cout << "cv1 after forEach (multiplying by 2): " << std::endl;
  cv1.print();
  std::cout << std::endl;

  rv1.forEach([](double& val) { val += 1; });
  std::cout << "rv1 after forEach (adding 1): " << std::endl;
  rv1.print();
  std::cout << std::endl;

  m1.forEach([](double& val) { val -= 1; });
  std::cout << "m1 after forEach (subtracting 1): " << std::endl;
  m1.print();
  std::cout << std::endl;

  return 0;
}