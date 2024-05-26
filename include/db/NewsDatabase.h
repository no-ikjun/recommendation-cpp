#ifndef NEWSDATABASE_H
#define NEWSDATABASE_H

#include "db/Database.h"
#include "data/News.h"
#include <memory>
#include <string>
#include <vector>

class NewsDatabase : public Database<News> {
public:
  explicit NewsDatabase(const std::string& filename);
  ~NewsDatabase();

  void add(News* item) override;
  std::vector<News*> getAllData() const override;
  News* getDataById(const std::string& id) const override;
  void modifyData(const std::string& id, News* item) override;

private:
  std::string filename; 
  mutable std::vector<std::unique_ptr<News>> newsList;

  void saveToFile() const;
  void loadFromFile();
};

#endif // NEWSDATABASE_H
