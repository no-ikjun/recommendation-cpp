#include "recommender/Recommender.h"
#include "recommender/Model.h"
#include "LinearAlgebra/ColumnVector.h"
#include "data/News.h"
#include "db/UserDatabase.h"

#include <iostream>
#include <vector>
#include <memory>

Recommender::Recommender(Model* model_ptr) : model_ptr(model_ptr), prevNewsId("1"), lastNewsId("1") {}

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
  std::cout << "bestNewsId: " << bestNewsId << std::endl;
  std::cout << "bestScore" << bestScore << std::endl;
  UserDatabase* userDb = UserDatabase::getInstance("./data/bin/user_database.bin");
  userDb->update(&user);
  prevNewsId = lastNewsId;
  lastNewsId = bestNewsId;
  return bestNewsId;
}

void Recommender::feedback(User& user, NewsDatabase* newsDatabase, bool isBetter, double sensitivity){
  std::vector<std::string> history = user.getHistory();
  for(auto& id : history){
    std::cout << id << std::endl;
  }
  News news = newsDatabase->get(lastNewsId);
  std::cout << "news: " << news.getId() << std::endl;
  News prevNews = newsDatabase->get(prevNewsId);
  std::cout << "prevNews: " << prevNews.getId() << std::endl;
  LinearAlgebra::ColumnVector userPreference = user.getPreference();
  LinearAlgebra::ColumnVector newsVector = model_ptr->embed(news.getContent());
  LinearAlgebra::ColumnVector prevNewsVector = model_ptr->embed(prevNews.getContent());
  LinearAlgebra::ColumnVector diff = newsVector - prevNewsVector;
  LinearAlgebra::ColumnVector newPreference = userPreference + diff * (isBetter ? sensitivity : -sensitivity);
  user.setPreference(newPreference);
}