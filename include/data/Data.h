#ifndef DATA_H
#define DATA_H

#include <string>

// Abstract class for any data type
class Data {
protected:
  Data(std::string id, std::string content);
  std::string getId();
  virtual std::string getContent() = 0;
private:
  std::string id;
  std::string content;
};

#endif