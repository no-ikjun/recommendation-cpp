#ifndef GLOBALCOMMAND_H
#define GLOBALCOMMAND_H

#include "db/UserDatabase.h"
#include "db/NewsDatabase.h"
#include "recommender/Model.h"
#include "recommender/Recommender.h"
#include <string>
#include <iostream>

class GlobalCommand {
private:
  UserDatabase* userDb;
  NewsDatabase* newsDb;
  Recommender* recommender;

public:
  explicit GlobalCommand(UserDatabase* userDb, NewsDatabase* newsDb, Recommender* recommender) : userDb(userDb), newsDb(newsDb), recommender(recommender) {}
  static bool continuePrompt();
  void showMenu();
  void showUserMenu();
  void printWelcome();
  void printGoodbye();
  void printError(const std::string& message);
};

#endif // GLOBALCOMMAND_H