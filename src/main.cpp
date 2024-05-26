#include <iostream>
#include "data/News.h"
#include "data/Category.h"
#include "db/NewsDatabase.h"
#include "db/UserDatabase.h"
#include <vector>
#include <memory>

int main() {
  std::string userFilename = "./data/user_database.bin";
  UserDatabase userDb(userFilename);

  // User 객체를 동적으로 생성하고 unique_ptr로 관리
  std::unique_ptr<User> user = std::make_unique<User>("1", "John Doe", "1234");
  userDb.add(user.get()); // add 메서드에 User 포인터를 넘김

  User* retrievedUser = userDb.getDataById("1");
  if (retrievedUser) {
    std::cout << "Retrieved User: " << retrievedUser->getName() << std::endl;
  } else {
    std::cout << "User not found." << std::endl;
  }

  std::string newsFilename = "./data/news_database.bin";
  NewsDatabase newsDb(newsFilename);

  // News 객체들을 동적으로 생성하고 unique_ptr로 관리
  std::unique_ptr<News> news1 = std::make_unique<News>("3", "AI Advances", "New AI algorithms have been developed.", Category::IT);
  std::unique_ptr<News> news2 = std::make_unique<News>("4", "Space Exploration", "Mars mission plans unveiled.", Category::SCIENCE);

  newsDb.add(news1.get());
  newsDb.add(news2.get());

  std::vector<News*> newsList = newsDb.getAllData();
  for (const News* news : newsList) {
    std::cout << "Retrieved News: " << news->getTitle() << " - " << news->getContent() << std::endl;
  }

  return 0;
}
