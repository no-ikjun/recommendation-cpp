#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "db/Database.h"
#include "data/User.h"
#include <string>
#include <vector>
#include <mutex>

class UserDatabase : public Database {
private:
  static UserDatabase* instance;
  static std::mutex mutex;
  std::string filename;

  explicit UserDatabase(const std::string& filename);

public:
  //복사 방지
  UserDatabase(const UserDatabase&) = delete;
  UserDatabase& operator=(const UserDatabase&) = delete;

  static UserDatabase* getInstance(const std::string& filename);

  void add(void* item) override;
  User get(std::string id);
  void saveToFile(const User& user);
  std::vector<User> loadFromFile();

  virtual ~UserDatabase() {}
};

#endif
