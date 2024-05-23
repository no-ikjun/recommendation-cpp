#include "NewsDatabase.h"

void NewsDatabase::addObserver(DatabaseObserver* observer) {
  observers.push_back(observer);
}

void NewsDatabase::add(void* item) {
  News* news = static_cast<News*>(item);
  newsList.push_back(*news);
  for (auto* observer : observers) {
    observer->onDataAdded(news);
  }
}

void NewsDatabase::update(void* item) {
  News* updatedNews = static_cast<News*>(item);
  for (auto& news : newsList) {
    if (news.getId() == updatedNews->getId()) {
      news = *updatedNews;
      for (auto* observer : observers) {
        observer->onDataUpdated(&news);
      }
      return;
    }
  }
}
