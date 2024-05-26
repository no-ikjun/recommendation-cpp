#include <string>
#include "data/Data.h"

Data::Data(std::string id, std::string content) {
  this->id = id;
  this->content = content;
}

std::string Data::getId() {
  return id;
}

std::string Data::getContent() {
  return content;
}