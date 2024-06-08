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

// 카테고리 문자열을 Category 열거형으로 변환하는 함수
Category parseCategory(const std::string& categoryStr) {
  if (categoryStr == "Entertainment") return Category::ENTERTAINMENT;
  else if (categoryStr == "science") return Category::SCIENCE;
  else if (categoryStr == "Health") return Category::HEALTH;
  else if (categoryStr == "Politics") return Category::POLITICS;
  else if (categoryStr == "Sports") return Category::SPORTS;
  else if (categoryStr == "World") return Category::WORLD;
  else if (categoryStr == "Tech") return Category::TECH;
  else if (categoryStr == "Business") return Category::BUSINESS;
  else return Category::NONE;
}

void loadNewsFromCSV(const std::string& filename, NewsDatabase* newsDb) {
  std::ifstream file(filename);
  std::string line;
  
  std::getline(file, line);

  std::cout << "Start loading news from " << filename << "\n";

  int id = 1;
  while (std::getline(file, line)) {
    if (id  > 300) break;
    std::istringstream ss(line);
    std::string text, categoryStr, dummy;
    
    std::getline(ss, dummy, '"');
    std::getline(ss, text, '"');
    std::getline(ss, dummy, ',');
    std::getline(ss, categoryStr, ',');

    Category category = parseCategory(categoryStr);
    News* news = new News(std::to_string(id), "Generated Title", text, category);
    newsDb->add(news);
    id++;
  }
  
  file.close();
}


int main() {
  //userDB 객체 생성
  std::string userFilename = "user_database.bin";
  UserDatabase* userDb = UserDatabase::getInstance(userFilename);
  //newsDB 객체 생성
  std::string newsFilename = "news_database.bin";
  NewsDatabase* newsDb = NewsDatabase::getInstance(newsFilename);
  //user session 객체 생성
  UserSession* session = UserSession::getInstance();

  GlobalCommand globalCommand(userDb, newsDb);
  globalCommand.printWelcome();
  
  while (!session->isAuthenticated()) {
    globalCommand.showMenu();
    if (session->isAuthenticated()) {
      std::cout << "Welcome, " << session->getUserName() << "!\n";
      break;
    }
  }

  //loadNewsFromCSV("news_article_categorization.csv", newsDb);

  // std::vector<News> newsList = newsDb->loadFromFile();
  // for (const auto& news : newsList) {
  //   std::cout << "Retrieved News: " << news.getId() << " - " << news.getContent() << std::endl;
  // }
  return 0;
}
