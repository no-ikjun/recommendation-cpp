#include "../../include/recommender/Recommender.h"
#include "../../include/recommender/Model.h"
#include "../../include/LinearAlgebra/ColumnVector.h"
#include "../../include/data/News.h"

#include <vector>

Recommender::Recommender(Model& model) : model(model) {}

std::string Recommender::getRecommendation(User& user, NewsDatabase& newsDatabase){
  LinearAlgebra::ColumnVector userPreference(user.getPreferences());
  std::vector<News> all_news = newsDatabase.loadFromFile();
  std::string bestNewsId;
  double bestScore = -1;
  for (const auto& news : all_news) {
    LinearAlgebra::ColumnVector newsVector = this->model.embed(news.getContent());
    double score = userPreference.cosineSimilarity(newsVector);
    if (score > bestScore) {
      bestScore = score;
      bestNewsId = news.getId();
    }
  }
  return bestNewsId;
}