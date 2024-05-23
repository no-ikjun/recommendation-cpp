#ifndef NEWSDATABASE_H
#define NEWSDATABASE_H

#include "db/Database.h"
#include "data/News.h"
#include <string>

class NewsDatabase : public Database {
private:
  std::string filename;

public:
  explicit NewsDatabase(const std::string& filename);

  void add(void* item);

  News get(std::string id);

  void saveToFile(const News& news);

  std::vector<News> loadFromFile();

  virtual ~NewsDatabase() {}
};

#endif
