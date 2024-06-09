#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "data/User.h"
#include "db/NewsDatabase.h"
#include "data/Data.h"
#include "recommender/Model.h"
#include "LinearAlgebra/ColumnVector.h"

#include <memory>
#include <string>
#include <vector>

class Recommender{
public:
  Recommender(Model* model_ptr);
  void embedContents(NewsDatabase&);
  LinearAlgebra::ColumnVector embedPreference(const std::string&);
  std::string getRecommendation(User, NewsDatabase*);

private:
  Model* model_ptr;
};

#endif