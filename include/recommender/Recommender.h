#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "data/User.h"
#include "db/NewsDatabase.h"
#include "data/Data.h"
#include "recommender/Model.h"

#include <memory>
#include <string>
#include <vector>

class Recommender{
public:
  Recommender(Model* model_ptr);
  void embedContents(NewsDatabase&);
  LinearAlgebra::ColumnVector embedPreference(const std::string&);
  std::string getRecommendation(User, NewsDatabase*);
  void feedback(User, NewsDatabase*, bool isBetter, double sensitivity);

private:
  Model* model_ptr;
  std::vector<std::string> history;
};

#endif