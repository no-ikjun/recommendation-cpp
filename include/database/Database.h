#include <string>
#include "../data/Data.h"
#include <vector>
#include <functional>
#include <memory>

class Database {
public:
  Database(std::string databaseId) {}
  std::string getDatabaseId() const {}
  std::shared_ptr<const Data> getDataById(std::string& id) const {}
  std::vector<Data> filter(std::function<bool(std::shared_ptr<const Data>)>) const {}
  
private:
  std::string databaseId;
};