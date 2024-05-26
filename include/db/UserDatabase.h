#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "db/Database.h"
#include "data/User.h"
#include <string>
#include <vector>

class UserDatabase : public Database {
private:
  std::string filename;

public:
  explicit UserDatabase(const std::string& filename);

  void add(void* item) override;

  User get(std::string id);

  void saveToFile(const User& user);

  std::vector<User> loadFromFile();

  virtual ~UserDatabase() {}
};

#endif