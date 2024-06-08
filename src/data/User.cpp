#include "data/User.h"
#include "LinearAlgebra/ColumnVector.h"
#include <iostream>

User::User() : id(""), name(""), password("") {}

User::User(const std::string& id, const std::string& name,
           const std::string& password)
    : id(id), name(name), password(password) {}

std::string User::getId() const { return id; }

std::string User::getName() const { return name; }

std::string User::getPassword() const { return password; }

LinearAlgebra::ColumnVector User::getPreference() const { return preference; }

void User::serialize(std::ostream& os) const {
  os.write(id.c_str(), id.size() + 1);
  os.write(name.c_str(), name.size() + 1);
  os.write(password.c_str(), password.size() + 1);
  os.write(reinterpret_cast<const char*>(&preference), sizeof(preference));
}

bool User::deserialize(std::istream& is) {
  std::getline(is, id, '\0');
  std::getline(is, name, '\0');
  std::getline(is, password, '\0');
  std::getline(is, reinterpret_cast<char*>(&preference), sizeof(preference));
  return !is.fail();
}