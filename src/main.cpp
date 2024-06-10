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

int main() {
  //userDB 객체 생성
  std::string userFilename = "./data/bin/user_database.bin";
  UserDatabase* userDb = UserDatabase::getInstance(userFilename);
  //newsDB 객체 생성
  std::string newsFilename = "./data/bin/news_database.bin";
  NewsDatabase* newsDb = NewsDatabase::getInstance(newsFilename);
  newsDb->loadFromCSV("./data/news_dataset/news_article_categorization.csv");
  //user session 객체 생성
  UserSession* session = UserSession::getInstance();

  // recommender 객체 생성
  Vocabulary vocabulary;
  vocabulary.loadFrom("./data/bin/vocabulary.bin");
  std::cout << vocabulary.getVocab().size() << std::endl;
  Word2Vec word2vec(300, 3, vocabulary);
  word2vec.loadWeights("./data/bin/weights");
  Recommender recommender(&word2vec);
  recommender.embedContents(*newsDb);
  std::cout << "2" << std::endl;

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
