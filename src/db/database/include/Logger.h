#ifndef LOGGER_H
#define LOGGER_H

#include "DatabaseObserver.h"
#include "News.h"
#include <iostream>

class Logger : public DatabaseObserver {
public:
  void onDataAdded(void* data) override;
  void onDataUpdated(void* data) override;
};

#endif // LOGGER_H
