#ifndef DATABASE_H
#define DATABASE_H

class Database {
public:
  virtual void add(void* item) = 0;

  template <typename T>
  T get();

  virtual ~Database() {}
};

#endif