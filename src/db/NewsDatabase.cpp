#include "db/NewsDatabase.h"
#include <fstream>
#include <iostream>
#include <vector>

NewsDatabase::NewsDatabase(const std::string& filename) : filename(filename) {
  // 생성자에서 특별한 초기화 작업은 필요 없음
}

void NewsDatabase::add(void* item) {
  // void 포인터를 News 객체로 변환
  News* news = static_cast<News*>(item);
  if (news) {
    saveToFile(*news); // 파일에 직접 뉴스를 저장
  }
}

News NewsDatabase::get(std::string id) {
  // 파일에서 뉴스를 불러와 해당 ID의 뉴스를 찾습니다.
  std::vector<News> newsList = loadFromFile();
  for (const auto& news : newsList) {
    if (news.getId() == id) {
      return news;
    }
  }
  // ID에 해당하는 뉴스가 없을 경우, 예외 처리가 필요하거나 기본 생성된 News 반환
  return News(); // ID가 없는 경우 빈 News 객체 반환
}

void NewsDatabase::saveToFile(const News& news) {
  // 파일을 추가 모드로 열어 새 뉴스를 덧붙입니다.
  std::ofstream file(filename, std::ios::binary | std::ios::app);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
    return;
  }
  news.serialize(file);
  file.close();
}

std::vector<News> NewsDatabase::loadFromFile() {
  // 파일로부터 모든 뉴스를 불러옵니다.
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