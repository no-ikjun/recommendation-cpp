// src/main.cpp
#include <iostream>
#include "data/News.h"
#include "data/User.h"
#include "data/Category.h"
#include "db/NewsDatabase.h"
#include "db/UserDatabase.h"
#include "command/UserCommand.h"
#include <vector>

int main() {
  //userDB 객체 생성
  std::string userFilename = "user_database.bin";
  UserDatabase* userDb = UserDatabase::getInstance(userFilename);
  //newsDB 객체 생성
  std::string newsFilename = "news_database.bin";
  NewsDatabase* newsDb = NewsDatabase::getInstance(newsFilename);

  //회원가입
  // UserCommand userCommand(userDb);
  // userCommand.signUp();

  //회원 정보 다 빼내기
  std::vector<User> userList = userDb->loadFromFile();
  for (const auto& user : userList) {
    std::cout << "Retrieved User: " << user.getId() << " - " << user.getName() << std::endl;
  }
 

  News news1("1", "AI Advances", "New AI algorithms have been developed.", Category::IT);
  News news2("2", "Space Exploration", "Mars mission plans unveiled.", Category::SCIENCE);

  newsDb->add(&news1);
  newsDb->add(&news2);

  std::vector<News> newsList = newsDb->loadFromFile();
  for (const auto& news : newsList) {
    std::cout << "Retrieved News: " << news.getTitle() << " - " << news.getContent() << std::endl;
  }

  return 0;
}
