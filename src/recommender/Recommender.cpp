#include "recommender/Recommender.h"
#include "recommender/Model.h"
#include "LinearAlgebra/ColumnVector.h"
#include "data/News.h"

#include <vector>
#include <memory>

Recommender::Recommender(Model* model_ptr) : model_ptr(model_ptr) {}

void Recommender::embedContents(NewsDatabase& newsDatabase){
  std::vector<News> all_news = newsDatabase.loadFromFile();
  for (auto& news : all_news) {
    news.setEmbedding(this->model_ptr->embed(news.getContent()));
    newsDatabase.saveToFile(news);
  }
}

LinearAlgebra::ColumnVector Recommender::embedPreference(const std::string& preference){
  return this->model_ptr->embed(preference);
}

std::string Recommender::getRecommendation(User user, NewsDatabase* newsDatabase){
  LinearAlgebra::ColumnVector userPreference(user.getPreference());
  std::vector<News> all_news = newsDatabase->loadFromFile();
  std::string bestNewsId;
  double bestScore = -1;
  for (const auto& news : all_news) {
    LinearAlgebra::ColumnVector newsVector = news.getEmbedding();
    double score = userPreference.cosineSimilarity(newsVector);
    if (score > bestScore) {
      bestScore = score;
      bestNewsId = news.getId();
    }
  }
  return bestNewsId;
}