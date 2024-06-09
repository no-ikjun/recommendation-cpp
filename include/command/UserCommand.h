#ifndef USERCOMMAND_H
#define USERCOMMAND_H

#include "db/UserDatabase.h"
#include "recommender/Model.h"
#include <string>

class UserCommand {
private:
  UserDatabase* userDb;

public:
  explicit UserCommand(UserDatabase* db) : userDb(db) {}
  void signUp();
  void signIn();
  void setPref(Model*);
  void printError(const std::string& message);
};

#endif // USERCOMMAND_H
