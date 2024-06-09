#include "data/User.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

User::User() : id(""), name(""), password(""), preference({}) {}

User::User(const std::string& id, const std::string& name,
           const std::string& password, const std::vector<double>& preference)
    : id(id), name(name), password(password), preference(preference) {}

std::string User::getId() const { return id; }

std::string User::getName() const { return name; }

std::string User::getPassword() const { return password; }

std::vector<double> User::getPreference() const { return preference; }

void User::setPreference(const std::vector<double>& preference) {
  this->preference = preference;
}

void User::serialize(std::ostream& os) const {
  os.write(id.c_str(), id.size() + 1);
  os.write(name.c_str(), name.size() + 1);
  os.write(password.c_str(), password.size() + 1);

  // Serialize the size of the preference vector first
  size_t size = preference.size();
  os.write(reinterpret_cast<const char*>(&size), sizeof(size));

  // Serialize each element in the preference vector
  for (double pref : preference) {
    os.write(reinterpret_cast<const char*>(&pref), sizeof(double));
  }
}

bool User::deserialize(std::istream& is) {
  std::getline(is, id, '\0');
  std::getline(is, name, '\0');
  std::getline(is, password, '\0');

  size_t size = 0;
  if (is.read(reinterpret_cast<char*>(&size), sizeof(size))) {
    preference.resize(size);
    for (size_t i = 0; i < size; ++i) {
      double pref;
      if (!is.read(reinterpret_cast<char*>(&pref), sizeof(double))) {
        return false;
      }
      preference[i] = pref;
    }
  } else {
    return false;
  }

  return !is.fail();
}