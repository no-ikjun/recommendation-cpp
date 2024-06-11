#include "recommender/Recommender.h"
#include "recommender/Model.h"
#include "LinearAlgebra/ColumnVector.h"
#include "data/News.h"
#include "db/UserDatabase.h"

#include <iostream>
#include <vector>
#include <memory>

Recommender::Recommender(Model* model_ptr) : model_ptr(model_ptr) {}

void Recommender::embedContents(NewsDatabase& newsDatabase){
  std::cout << "Embedding news contents..." << std::endl;
  std::vector<News> all_news = newsDatabase.loadFromFile();
  for (auto& news : all_news) {
    news.setEmbedding(this->model_ptr->embed(news.getContent()));
    newsDatabase.saveToFile(news);
  }
  std::cout << "Done." << std::endl;
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
  user.addHistory(bestNewsId);
  UserDatabase* userDb = UserDatabase::getInstance("./data/bin/user_database.bin");
  userDb->update(&user);
  return bestNewsId;
}

void Recommender::feedback(User user, NewsDatabase* newsDatabase, bool isBetter, double sensitivity){
  std::vector<std::string> history = user.getHistory();
  News news = newsDatabase->get(history[history.size() - 2]);
  News prevNews = newsDatabase->get(history.back());
  LinearAlgebra::ColumnVector userPreference = user.getPreference();
  LinearAlgebra::ColumnVector newsVector = news.getEmbedding();
  LinearAlgebra::ColumnVector prevNewsVector = prevNews.getEmbedding();
  LinearAlgebra::ColumnVector diff = newsVector - prevNewsVector;
  LinearAlgebra::ColumnVector newPreference = userPreference + diff * (isBetter ? sensitivity : -sensitivity);
  user.setPreference(newPreference);
}