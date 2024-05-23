#ifndef NEWSDATABASE_H
#define NEWSDATABASE_H

#include "Database.h"
#include "DatabaseObserver.h"
#include "News.h"
#include <vector>

class NewsDatabase : public Database {
private:
  std::vector<News> newsList;
  std::vector<DatabaseObserver*> observers;

public:
  void addObserver(DatabaseObserver* observer);
  void add(void* item) override;
  void update(void* item) override;
};

#endif // NEWSDATABASE_H
