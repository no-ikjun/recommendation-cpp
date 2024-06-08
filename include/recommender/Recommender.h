#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "User.h"
#include "NewsDatabase.h"
#include "Data.h"
#include "Model.h"

#include <memory>
#include <string>
#include <vector>

class Recommender{
public:
  Recommender(Model&);
  std::string getRecommendation(User&, NewsDatabase&);

private:
  Model model;
};

#endif