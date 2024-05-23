#ifndef DATABASEOBSERVER_H
#define DATABASEOBSERVER_H

class DatabaseObserver {
public:
  virtual ~DatabaseObserver() {}
  virtual void onDataAdded(void* data) = 0;
  virtual void onDataUpdated(void* data) = 0;
};

#endif // DATABASEOBSERVER_H
