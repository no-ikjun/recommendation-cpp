#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "db/Database.h"
#include "data/User.h"
#include <memory>
#include <string>
#include <vector>

class UserDatabase : public Database<User> {
public:
  explicit UserDatabase(const std::string& filename);
  ~UserDatabase();

  void add(std::unique_ptr<User> item) override;
  std::vector<User*> getAllData() const override;
  User* getDataById(const std::string& id) const override;
  void modifyData(const std::string& id, User* item) override;

private:
  std::string filename; 
  mutable std::vector<std::unique_ptr<User>> userList;

  void saveToFile() const override;
  void loadFromFile() override;
};

#endif // USERDATABASE_H
