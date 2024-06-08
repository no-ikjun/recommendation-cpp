#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
  User();
  User(const std::string& id, const std::string& name, const std::string& password);

  std::string getId() const;
  std::string getName() const;
  std::string getPassword() const;
  std::vector<double> getPreference() const;
  void setPreference(const std::vector<double>& preference);

  void serialize(std::ostream& os) const;
  bool deserialize(std::istream& is);

private:
  std::string id;
  std::string name;
  std::string password;
  std::vector<double> preference;
};

#endif // USER_H