#include "db/NewsDatabase.h"
#include "data/News.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

NewsDatabase::NewsDatabase(const std::string& filename) : filename(filename) {}

void NewsDatabase::add(void* item) {
  News* news = static_cast<News*>(item);
  saveToFile(*news);
}

News NewsDatabase::get(std::string id) {
  std::vector<News> newsList = loadFromFile();
  //TODO: 특정 id 값을 가진 뉴스를 찾아서 반환
  return newsList.front();
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

  while (file.peek() != std::ifstream::traits_type::eof()) {
    News news; // If this line causes error, change it to dynamic allocation or ensure parameters ready
    if (news.deserialize(file)) {
      newsList.push_back(news);
    }
  }
  file.close();
  return newsList;
}


