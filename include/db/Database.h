#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <vector>

template<typename T>
class Database {
public:
  virtual void add(std::unique_ptr<T> item) = 0;
  virtual std::vector<T*> getAllData() const = 0;
  virtual T* getDataById(const std::string& id) const = 0;
  virtual void modifyData(const std::string& id, T* item) = 0;
  virtual ~Database() {}

protected:
  virtual void saveToFile() const = 0;
  virtual void loadFromFile() = 0;
};

#endif // DATABASE_H
