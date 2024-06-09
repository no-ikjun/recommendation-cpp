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
  Recommender(Model&);
  std::string getRecommendation(User&, NewsDatabase&);

private:
  Model& model;
};

#endif