#include "Logger.h"

void Logger::onDataAdded(void* data) {
  News* news = static_cast<News*>(data);
  std::cout << "News added: " << news->getTitle() << std::endl;
}

void Logger::onDataUpdated(void* data) {
  News* news = static_cast<News*>(data);
  std::cout << "News updated: " << news->getTitle() << std::endl;
}
