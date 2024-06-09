#ifndef NEWSCOMMAND_H
#define NEWSCOMMAND_H

#include "db/NewsDatabase.h"
#include <string>

class NewsCommand {
private:
  NewsDatabase* newsDb;

public:
  explicit NewsCommand(NewsDatabase* db) : newsDb(db) {}
  void getRecommendation();
  bool printNews(std::string id);
  void printError(const std::string& message);
};

#endif // NEWSCOMMAND_H