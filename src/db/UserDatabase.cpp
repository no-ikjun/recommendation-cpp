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
  std::cout << "1" << std::endl;
  User* user = static_cast<User*>(item);
  std::cout << "2" << std::endl;
  if (user) {
    try {
      std::cout << "3" << std::endl;
      User duplicatedUser = get(user->getId());
      std::cout << "4" << std::endl;
      if (duplicatedUser.getId() == user->getId()) {
        throw std::runtime_error("User with id " + user->getId() + " already exists.");
      }
      std::cout << "5" << std::endl;
    } catch (const std::invalid_argument& e) {
      std::cout << "6" << std::endl;
      saveToFile(*user);
      std::cout << "7" << std::endl;
    }
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
  while (user.deserialize(file)) {
    userList.push_back(user);
  }
  file.close();
  return userList;
}

void UserDatabase::update(std::string id, void* item) {
  User* newUser = static_cast<User*>(item);
  if (newUser) {
    std::vector<User> userList = loadFromFile();
    bool updated = false;
    for (auto& user : userList) {
      if (user.getId() == id) {
        user = *newUser;
        updated = true;
        break;
      }
    }
    if (updated) {
      std::ofstream file(filename, std::ios::binary);
      if (file) {
        for (const auto& user : userList) {
          user.serialize(file);
        }
      } else {
        std::cerr << "Cannot open file " << filename << " for writing." << std::endl;
      }
      file.close();
    }
  } else {
    std::cerr << "Error: Null user pointer passed to update function." << std::endl;
  }
}