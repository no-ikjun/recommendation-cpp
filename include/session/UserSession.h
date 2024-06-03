#ifndef USERSESSION_H
#define USERSESSION_H

#include <string>
#include <mutex>

class UserSession {
private:
  static UserSession* instance;
  static std::mutex mutex;
  bool isLoggedIn;
  std::string userId;
  std::string userName;
  
  // Private constructor for singleton pattern
  UserSession() : isLoggedIn(false) {}

public:
  UserSession(const UserSession&) = delete;
  UserSession& operator=(const UserSession&) = delete;

  static UserSession* getInstance();
  
  void login(const std::string& id, const std::string& name);
  void logout();
  bool isAuthenticated() const;
  std::string getUserId() const;
  std::string getUserName() const;
};

#endif // USERSESSION_H
