#include "db/UserDatabase.h"
#include <fstream>
#include <iostream>

UserDatabase::UserDatabase(const std::string& filename) : filename(filename) {
  loadFromFile();
}

UserDatabase::~UserDatabase() {
  saveToFile();
}

void UserDatabase::add(std::unique_ptr<User> item) {
  userList.push_back(std::move(item));
  saveToFile();
}

std::vector<User*> UserDatabase::getAllData() const {
  std::cerr << "getAllData is not supported for UserDatabase." << std::endl;
  throw std::logic_error("Operation not supported");
  return std::vector<User*>();
}

User* UserDatabase::getDataById(const std::string& id) const {
  for (const auto& user : userList) {
    if (user->getId() == id) {
      return user.get();
    }
  }
  return nullptr;
}

void UserDatabase::modifyData(const std::string& id, User* item) {
  for (auto& user : userList) {
    if (user->getId() == id) {
      user.reset(item);
      saveToFile();
      break;
    }
  }
}

void UserDatabase::saveToFile() const {
  std::ofstream file(filename, std::ios::binary | std::ios::trunc);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
    return;
  }
  for (const auto& user : userList) {
    user->serialize(file);
  }
  file.close();
}

void UserDatabase::loadFromFile() {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for reading." << std::endl;
    return;
  }
  User* user = nullptr;
  while ((user = new User(), user->deserialize(file))) {
    userList.push_back(std::unique_ptr<User>(user));
  }
  file.close();
}
