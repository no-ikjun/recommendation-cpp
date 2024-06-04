#include "session/UserSession.h"

UserSession* UserSession::instance = nullptr;
std::mutex UserSession::mutex;

UserSession* UserSession::getInstance() {
  std::lock_guard<std::mutex> lock(mutex);
  if (instance == nullptr) {
      instance = new UserSession();
  }
  return instance;
}

void UserSession::login(const std::string& id, const std::string& name) {
  userId = id;
  userName = name;
  isLoggedIn = true;
}

void UserSession::logout() {
  userId = "";
  userName = "";
  isLoggedIn = false;
}

bool UserSession::isAuthenticated() const {
  return isLoggedIn;
}

std::string UserSession::getUserId() const {
  return userId;
}

std::string UserSession::getUserName() const {
  return userName;
}
