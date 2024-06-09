#ifndef USERCOMMAND_H
#define USERCOMMAND_H

#include "db/UserDatabase.h"
#include "recommender/Recommender.h"
#include <string>

class UserCommand {
private:
  UserDatabase* userDb;

public:
  explicit UserCommand(UserDatabase* db) : userDb(db) {}
  void signUp();
  void signIn();
  void setPref(Recommender* recommender);
  void printError(const std::string& message);
};

#endif // USERCOMMAND_H
