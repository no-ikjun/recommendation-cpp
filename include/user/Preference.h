#include <string>
#include "../ui/Command.h"
#include "../database/Database.h"

class Preference {
public:
  Preference(std::string userId, Database* newsDb) {}
  void update(Command);
  void clear();
private:
  std::string userId;
  Database* database;
};