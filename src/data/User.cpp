#include "data/User.h"
#include "LinearAlgebra/ColumnVector.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

User::User() : id(""), name(""), password(""), preference(LinearAlgebra::ColumnVector(1)), history({}) {}

User::User(const std::string& id, 
           const std::string& name,
           const std::string& password, 
           const LinearAlgebra::ColumnVector& preference = LinearAlgebra::ColumnVector(1))
    : id(id), name(name), password(password), preference(preference), history({}) {}

// // 복사 생성자
// User::User(const User& other)
//   : id(other.id), name(other.name), password(other.password),
//     preference(other.preference), history(other.history) {}

// // 대입 연산자
// User& User::operator=(const User& other) {
//   if (this != &other) {
//     id = other.id;
//     name = other.name;
//     password = other.password;
//     preference = other.preference; //이부분 안될수도 있음
//     history = other.history;
//   }
//   return *this;
// }

std::string User::getId() const { return id; }

std::string User::getName() const { return name; }

std::string User::getPassword() const { return password; }

LinearAlgebra::ColumnVector User::getPreference() const { return preference; }

void User::setPreference(const LinearAlgebra::ColumnVector& preference) {
  this->preference = preference;
}

void User::addHistory(const std::string& newsId) {
  history.push_back(newsId);
}

std::vector<std::string> User::getHistory() const {
  return history;
}

void User::serialize(std::ostream& os) const {
  os.write(id.c_str(), id.size() + 1);  // Include null terminator
  os.write(name.c_str(), name.size() + 1);  // Include null terminator
  os.write(password.c_str(), password.size() + 1);  // Include null terminator
  preference.serialize(os);

  // Serialize history
  if (history.empty()) {
    os << '\0';  // Write a null terminator if history is empty
  } else {
    for (size_t i = 0; i < history.size(); ++i) {
      if (i > 0) os << ",";
      os << history[i];
    }
    os << '\0';  // End history with a null terminator
  }
}


bool User::deserialize(std::istream& is) {
  try {
    if (!std::getline(is, id, '\0')) return false;  // Read ID
    if (!std::getline(is, name, '\0')) return false;  // Read name
    if (!std::getline(is, password, '\0')) return false;  // Read password
    preference.deserialize(is);  // Read preference

    // Read history
    history.clear();  // Clear existing history
    std::string historyStr;
    if (!std::getline(is, historyStr, '\0')) return false;
    std::istringstream historyStream(historyStr);
    std::string newsId;
    while (std::getline(historyStream, newsId, ',')) {
      if (!newsId.empty()) {
        history.push_back(newsId);
      }
    }

    return true;
  } catch (const std::exception& e) {
    std::cerr << "Failed to deserialize user data: " << e.what() << std::endl;
    return false;
  }
}
