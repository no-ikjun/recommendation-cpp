// src/main.cpp
#include <iostream>
#include "data/News.h"
#include "data/User.h"
#include "data/Category.h"
#include "db/NewsDatabase.h"
#include "db/UserDatabase.h"
#include "command/GlobalCommand.h"
#include "command/UserCommand.h"
#include "session/UserSession.h"
#include "recommender/Recommender.h"
#include "recommender/Word2Vec.h"
#include "recommender/Vocabulary.h"
#include "recommender/Model.h"
#include <vector>
#include <fstream>
#include <sstream>

#define USER_DB_FILEPATH "./data/bin/user_database.bin"
#define NEWS_DB_FILEPATH "./data/bin/news_database.bin"
#define NEWS_DATASET_FILEPATH "./data/news_dataset/news_article_categorization.csv"

int main() {
  UserDatabase* userDb = UserDatabase::getInstance(USER_DB_FILEPATH);
  NewsDatabase* newsDb = NewsDatabase::getInstance(NEWS_DB_FILEPATH);
  newsDb->loadFromCSV(NEWS_DATASET_FILEPATH);
  UserSession* session = UserSession::getInstance();
  Vocabulary vocabulary;
  vocabulary.loadFrom("./data/bin/vocabulary.bin");
  Word2Vec word2vec(300, 3, vocabulary);  
  word2vec.loadWeights("./data/bin/weights");
  Recommender recommender(&word2vec);
  recommender.embedContents(*newsDb); //TODO: save news with embeddings

  GlobalCommand globalCommand(userDb, newsDb, &recommender);
  globalCommand.printWelcome();
  
  while (!session->isAuthenticated()) {
    globalCommand.showMenu();
  }

  if (session->isAuthenticated()) {
    globalCommand.showUserMenu();
  }

  // std::vector<User> userList = userDb->loadFromFile();
  // for (const auto& user : userList) {
  //   std::cout << "Retrieved User: " << user.getId() << " - " << user.getName() << std::endl;
  // }

  //loadNewsFromCSV("./data/news_dataset/news_article_categorization.csv", newsDb);

  // std::vector<News> newsList = newsDb->loadFromFile();
  // for (const auto& news : newsList) {
  //   std::cout << "Retrieved News: " << news.getId() << " - " << news.getContent() << std::endl;
  // }
  return 0;
}
