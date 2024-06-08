#ifndef MODEL_H
#define MODEL_H

#include "../LinearAlgebra/ColumnVector.h"

#include <vector>
#include <string>

class Model {
public: 
  virtual LinearAlgebra::ColumnVector embed(std::string) = 0;
};

#endif