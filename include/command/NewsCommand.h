#ifndef NEWSCOMMAND_H
#define NEWSCOMMAND_H

#include "db/NewsDatabase.h"
#include "db/UserDatabase.h"
#include <string>

class NewsCommand {
private:
  NewsDatabase* newsDb;
  UserDatabase* userDb;

public:
  explicit NewsCommand(NewsDatabase* newsDb, UserDatabase* userDb) : newsDb(newsDb), userDb(userDb) {}
  void getRecommendation();
  bool printNews(std::string id);
  void printError(const std::string& message);
};

#endif // NEWSCOMMAND_H