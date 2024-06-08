#ifndef NEWSCOMMAND_H
#define NEWSCOMMAND_H

#include "db/NewsDatabase.h"
#include <string>

class NewsCommand {
private:
  NewsDatabase* newsDb;

public:
  explicit NewsCommand(NewsDatabase* db) : newsDb(db) {}
  void printNews(string id);
  void printError(const std::string& message);
};

#endif // NEWSCOMMAND_H