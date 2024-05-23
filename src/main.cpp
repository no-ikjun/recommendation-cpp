// src/main.cpp
#include <iostream>
#include "data/News.h"
#include "data/Category.h"
#include "db/NewsDatabase.h"
#include <vector>

int main() {
  std::string filename = "news_database.bin";
  NewsDatabase db(filename);

  News news1("1", "AI Advances", "New AI algorithms have been developed.", Category::IT);
  News news2("2", "Space Exploration", "Mars mission plans unveiled.", Category::SCIENCE);

  db.add(&news1);
  db.add(&news2);

  std::vector<News> newsList = db.loadFromFile();
  for (const auto& news : newsList) {
    std::cout << "Retrieved News: " << news.getTitle() << " - " << news.getContent() << std::endl;
  }

  return 0;
}
