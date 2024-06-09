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
  //user session 객체 생성
  UserSession* session = UserSession::getInstance();

  GlobalCommand globalCommand(userDb, newsDb);
  globalCommand.printWelcome();
  
  while (!session->isAuthenticated()) {
    globalCommand.showMenu();
    if (session->isAuthenticated()) {
      globalCommand.showUserMenu();
      break;
    }
  }

  // std::vector<User> userList = userDb->loadFromFile();
  // for (const auto& user : userList) {
  //   printPreferences(user.getPreference());
  // }

  //loadNewsFromCSV("./data/news_dataset/news_article_categorization.csv", newsDb);

  // std::vector<News> newsList = newsDb->loadFromFile();
  // for (const auto& news : newsList) {
  //   std::cout << "Retrieved News: " << news.getId() << " - " << news.getContent() << std::endl;
  // }
  return 0;
}
