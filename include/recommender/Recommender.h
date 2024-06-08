#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include "User.h"
#include "NewsDatabase.h"
#include "Data.h"
#include "Model.h"

#include <memory>
#include <string>

class Recommender{
public:
  Recommender(User&, std::unique_ptr<NewsDatabase>, Model&);
  std::unique_ptr<Data> getRecommendation();
  void updatePreference(std::string contentId, bool feedback);
  void reset();

private:
  User user;
  std::unique_ptr<NewsDatabase> newsDatabase;
  Model model;

  std::string prevRecommendedContentID;
};

#endif