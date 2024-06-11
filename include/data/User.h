#ifndef USER_H
#define USER_H

#include "LinearAlgebra/ColumnVector.h"
#include <string>
#include <vector>

class User {
public:
  User();
  User(const std::string& id,
       const std::string& name,
       const std::string& password,
       const LinearAlgebra::ColumnVector& preference);
  
  // User(const User& other);
  // User& operator=(const User& other);

  std::string getId() const;
  std::string getName() const;
  std::string getPassword() const;
  LinearAlgebra::ColumnVector getPreference() const;
  void setPreference(const LinearAlgebra::ColumnVector& preference);
  void addHistory(const std::string& newsId);
  std::vector<std::string> getHistory() const;

  void serialize(std::ostream& os) const;
  bool deserialize(std::istream& is);

private:
  std::string id;
  std::string name;
  std::string password;
  LinearAlgebra::ColumnVector preference;
  std::vector<std::string> history;
};

#endif // USER_H