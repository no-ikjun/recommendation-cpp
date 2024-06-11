#include "db/UserDatabase.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <mutex>
#include <vector>

UserDatabase* UserDatabase::instance = nullptr;
std::mutex UserDatabase::mutex;

// 생성자
UserDatabase::UserDatabase(const std::string& filename) : filename(filename) {}

// 싱글턴 인스턴스 반환 함수
UserDatabase* UserDatabase::getInstance(const std::string& filename) {
  std::lock_guard<std::mutex> lock(mutex);
  if (instance == nullptr) {
    instance = new UserDatabase(filename);
  }
  return instance;
}

void UserDatabase::add(void* item) {
  User* user = static_cast<User*>(item);
  if (user) {
    saveToFile(*user);
    // try {
    //   User duplicatedUser = get(user->getId());
    //   if (duplicatedUser.getId() == user->getId()) {
    //     throw std::runtime_error("User with id " + user->getId() + " already exists.");
    //   }
    // } catch (const std::invalid_argument& e) {
    //   saveToFile(*user);
    // }
  } else {
    std::cerr << "Error: Null user pointer passed to add function." << std::endl;
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
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Cannot open file " << filename << " for reading." << std::endl;
    return userList;
  }
  User user;
  while (file && user.deserialize(file)) {
    userList.push_back(user);
  }
  file.close();
  return userList;
}

void UserDatabase::update(User* updatedUser) {
  if (!updatedUser) {
    std::cerr << "Error: Null user pointer passed to update function." << std::endl;
    return;
  }
  std::vector<User> userList = loadFromFile();
  bool updated = false;
  for (auto& user : userList) {
    if (user.getId() == updatedUser->getId()) {
      user = *updatedUser;
      updated = true;
      break;
    }
  }
  if (updated) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
      std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
      return;
    }
    for (const auto& user : userList) {
      user.serialize(file);
      if (!file) {
        std::cerr << "Failed to write user data to file." << std::endl;
        return;
      }
    }
    file.close();
    std::cout << "User with id " << updatedUser->getId() << " updated successfully." << std::endl;
  }
}
