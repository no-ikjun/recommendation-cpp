#include "data/User.h"
#include "LinearAlgebra/ColumnVector.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

User::User() : id(""), name(""), password(""), preference(LinearAlgebra::ColumnVector(1)) {}

User::User(const std::string& id, 
           const std::string& name,
           const std::string& password, 
           const LinearAlgebra::ColumnVector& preference = LinearAlgebra::ColumnVector(1))
    : id(id), name(name), password(password), preference(preference) {}

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
  os.write(id.c_str(), id.size() + 1);
  os.write(name.c_str(), name.size() + 1);
  os.write(password.c_str(), password.size() + 1);
  preference.serialize(os);
}

bool User::deserialize(std::istream& is) {
  std::getline(is, id, '\0');
  std::getline(is, name, '\0');
  std::getline(is, password, '\0');
  preference.deserialize(is);
  return !is.fail();
}