#ifndef USERCOMMAND_H
#define USERCOMMAND_H

#include "db/UserDatabase.h"
#include <string>

class UserCommand {
private:
  UserDatabase* userDb;

public:
  explicit UserCommand(UserDatabase* db) : userDb(db) {}
  void signUp();
  void signIn();
  void setPref();
  void printError(const std::string& message);
  void printWelcome();
  void printGoodbye();
};

#endif // USERCOMMAND_H
