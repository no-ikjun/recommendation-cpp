#include <iostream>
#include "data/News.h"
#include "data/Category.h"
#include "data/User.h"
#include "db/NewsDatabase.h"
#include "db/UserDatabase.h"
#include <vector>
#include <memory>

int main() {
  std::string userFilename = "./data/user_database.bin";
  UserDatabase userDb(userFilename);

  auto user = std::make_unique<User>("1", "John Doe", "1234");
  userDb.add(std::move(user));  // UserDatabase는 std::unique_ptr<User>를 받도록 수정

  User* retrievedUser = userDb.getDataById("1");
  if (retrievedUser) {
    std::cout << "Retrieved User: " << retrievedUser->getName() << std::endl;
  } else {
    std::cout << "User not found." << std::endl;
  }

  std::string newsFilename = "./data/news_database.bin";
  NewsDatabase newsDb(newsFilename);

  auto news1 = std::make_unique<News>("3", "AI Advances", "New AI algorithms have been developed.", Category::IT);
  auto news2 = std::make_unique<News>("4", "Space Exploration", "Mars mission plans unveiled.", Category::SCIENCE);

  newsDb.add(std::move(news1));
  newsDb.add(std::move(news2));

  std::vector<News*> newsList = newsDb.getAllData();
  for (const News* news : newsList) {
    std::cout << "Retrieved News: " << news->getTitle() << " - " << news->getContent() << std::endl;
  }

  return 0;
}
