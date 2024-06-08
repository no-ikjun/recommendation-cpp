#ifndef GLOBALCOMMAND_H
#define GLOBALCOMMAND_H

#include "db/UserDatabase.h"
#include "db/NewsDatabase.h"
#include <string>
#include <iostream>

class GlobalCommand {
private:
  UserDatabase* userDb;
  NewsDatabase* newsDb;

public:
  explicit GlobalCommand(UserDatabase* userDb, NewsDatabase* newsDb) : userDb(userDb), newsDb(newsDb) {}
  static bool continuePrompt();
  void showMenu();
  void showUserMenu();
  void printWelcome();
  void printGoodbye();
  void printError(const std::string& message);
};

#endif // GLOBALCOMMAND_H