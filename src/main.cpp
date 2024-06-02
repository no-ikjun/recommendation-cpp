// src/main.cpp
#include <iostream>
#include "data/News.h"
#include "data/User.h"
#include "data/Category.h"
#include "db/NewsDatabase.h"
#include "db/UserDatabase.h"
#include <vector>

bool continuePrompt() {
  std::string response;
  while (true) {
    std::cout << "Do you want to try again? (y/n): ";
    std::getline(std::cin, response);
    if (response == "y" || response == "Y") {
        return true;
    } else if (response == "n" || response == "N") {
        return false;
    } else {
        std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
    }
  }
}

void signUp(UserDatabase& userDb) {
  while (true) {
    try {
      std::string id, name, password;
      std::cout << "Sign Up" << std::endl;

      std::cout << "id: ";
      std::getline(std::cin, id);
      std::cout << "name: ";
      std::getline(std::cin, name);
      std::cout << "password: ";
      std::getline(std::cin, password);

      User user(id, name, password);
      userDb.add(&user);
      break;  // 성공적으로 추가되면 반복 종료
    } catch (const std::runtime_error& e) {
      std::cout << "Error: " << e.what() << std::endl;
      if (!continuePrompt()) {
          break;  // 사용자가 'n' 입력시 종료
      }
    }
  }
}

int main() {
  //userDB 객체 생성
  std::string userFilename = "user_database.bin";
  UserDatabase userDb(userFilename);
  //newsDB 객체 생성
  std::string newsFilename = "news_database.bin";
  NewsDatabase db(newsFilename);

  //회원가입
  signUp(userDb);

  //회원 정보 다 빼내기
  std::vector<User> userList = userDb.loadFromFile();
  for (const auto& user : userList) {
    std::cout << "Retrieved User: " << user.getId() << " - " << user.getName() << std::endl;
  }
 

  // News news1("1", "AI Advances", "New AI algorithms have been developed.", Category::IT);
  // News news2("2", "Space Exploration", "Mars mission plans unveiled.", Category::SCIENCE);

  // db.add(&news1);
  // db.add(&news2);

  // std::vector<News> newsList = db.loadFromFile();
  // for (const auto& news : newsList) {
  //   std::cout << "Retrieved News: " << news.getTitle() << " - " << news.getContent() << std::endl;
  // }

  return 0;
}
