#include "db/NewsDatabase.h"
#include <fstream>
#include <iostream>
#include <vector>

NewsDatabase::NewsDatabase(const std::string& filename) : filename(filename) {
  // constructor implementation
}

void NewsDatabase::add(void* item) {
  News* news = static_cast<News*>(item);
  if (news) {
    saveToFile(*news);
  }
}

News NewsDatabase::get(std::string id) {
  std::vector<News> newsList = loadFromFile();
  for (const auto& news : newsList) {
    if (news.getId() == id) {
      return news;
    }
  }
  throw std::invalid_argument("No news with id " + id + " found.");
}

void NewsDatabase::saveToFile(const News& news) {
  std::ofstream file(filename, std::ios::binary | std::ios::app);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
    return;
  }
  news.serialize(file);
  file.close();
}

std::vector<News> NewsDatabase::loadFromFile() {
  std::vector<News> newsList;
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for reading." << std::endl;
    return newsList;
  }
  News news;
  while (news.deserialize(file)) {
    newsList.push_back(news);
  }
  file.close();
  return newsList;
}