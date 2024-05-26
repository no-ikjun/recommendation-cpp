#include "db/NewsDatabase.h"
#include <fstream>
#include <iostream>

NewsDatabase::NewsDatabase(const std::string& filename) : filename(filename) {
  loadFromFile();
}

NewsDatabase::~NewsDatabase() {
  saveToFile();
}

void NewsDatabase::add(News* item) {
  newsList.push_back(std::unique_ptr<News>(item));
  saveToFile();
}

std::vector<News*> NewsDatabase::getAllData() const {
  std::vector<News*> plainList;
  for (const auto& news : newsList) {
    plainList.push_back(news.get());
  }
  return plainList;
}

News* NewsDatabase::getDataById(const std::string& id) const {
  for (const auto& news : newsList) {
    if (news->getId() == id) {
      return news.get();
    }
  }
  return nullptr;
}

void NewsDatabase::modifyData(const std::string& id, News* item) {
  for (auto& news : newsList) {
    if (news->getId() == id) {
      news.reset(item);
      saveToFile();
      break;
    }
  }
}

void NewsDatabase::saveToFile() const {
  std::ofstream file(filename, std::ios::binary | std::ios::trunc);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
    return;
  }
  for (const auto& news : newsList) {
    news->serialize(file);
  }
  file.close();
}

void NewsDatabase::loadFromFile() {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for reading." << std::endl;
    return;
  }
  News* news = nullptr;
  while ((news = new News(), news->deserialize(file))) {
    newsList.push_back(std::unique_ptr<News>(news));
  }
  file.close();
}
