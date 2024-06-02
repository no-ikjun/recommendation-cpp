#include "db/UserDatabase.h"
#include <fstream>
#include <iostream>
#include <vector>

UserDatabase::UserDatabase(const std::string& filename) : filename(filename) {
  // constructor implementation
}

void UserDatabase::add(void* item) {
  User* user = static_cast<User*>(item);
  User duplicatedUser = get(user->getId());
  if (duplicatedUser.getId() == user->getId()) {
    throw std::runtime_error("User with id " + user->getId() + " already exists.");
  }
  if (user) {
    saveToFile(*user);
  }
}

User UserDatabase::get(std::string id) {
  std::vector<User> userList = loadFromFile();
  for (const auto& user : userList) {
    if (user.getId() == id) {
      return user;
    }
  }
  throw std::invalid_argument("No user with id " + id + " found.");
}

void UserDatabase::saveToFile(const User& user) {
  std::ofstream file(filename, std::ios::binary | std::ios::app);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
    return;
  }
  user.serialize(file);
  file.close();
}

std::vector<User> UserDatabase::loadFromFile() {
  std::vector<User> userList;
  std::ifstream file (filename, std::ios::binary);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for reading." << std::endl;
    return userList;
  }
  User user;
  while (user.deserialize(file)) {
    userList.push_back(user);
  }
  file.close();
  return userList;
}
