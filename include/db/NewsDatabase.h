#ifndef NEWSDATABASE_H
#define NEWSDATABASE_H

#include "db/Database.h"
#include "data/News.h"
#include <string>
#include <vector>
#include <mutex>

class NewsDatabase : public Database {
private:
  static NewsDatabase* instance;
  static std::mutex mutex;
  std::string filename;

  explicit NewsDatabase(const std::string& filename);

public:
  //복사 방지
  NewsDatabase(const NewsDatabase&) = delete;
  NewsDatabase& operator=(const NewsDatabase&) = delete;

  static NewsDatabase* getInstance(const std::string& filename);

  void add(void* item) override;
  News get(std::string id);
  void saveToFile(const News& news);
  std::vector<News> loadFromFile();

  virtual ~NewsDatabase() {}
};

#endif
