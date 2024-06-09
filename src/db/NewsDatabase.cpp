#include "db/NewsDatabase.h"
#include "data/News.h"
#include "data/Category.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <mutex>
#include <vector>
#include <sstream>

NewsDatabase* NewsDatabase::instance = nullptr;
std::mutex NewsDatabase::mutex;

NewsDatabase::NewsDatabase(const std::string& filename) : filename(filename) {}

// 싱글턴 인스턴스 반환 함수
NewsDatabase* NewsDatabase::getInstance(const std::string& filename) {
  std::lock_guard<std::mutex> lock(mutex);
  if (instance == nullptr) {
    instance = new NewsDatabase(filename);
  }
  return instance;
}

void NewsDatabase::add(void* item) {
  News* news = static_cast<News*>(item);
  if (news) {
    try {
      News duplicatedNews = get(news->getId());
      if (duplicatedNews.getId() == news->getId()) {
        throw std::runtime_error("News with id " + news->getId() + " already exists.");
      }
    } catch (const std::invalid_argument& e) {
      saveToFile(*news);
    }
  } else {
    std::cerr << "Error: Null news pointer passed to add function." << std::endl;
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

void NewsDatabase::loadFromCSV(const std::string& filename) {
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
    this->saveToFile(*news);
    id++;
  }
}