#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

template<typename T>
class Database {
public:
  virtual void add(T* item) = 0;
  virtual std::vector<T*> getAllData() const = 0;
  virtual T* getDataById(const std::string& id) const = 0;
  virtual void modifyData(const std::string& id, T* item) = 0;
  virtual ~Database() {}
};

#endif // DATABASE_H
