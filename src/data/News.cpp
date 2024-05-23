#include <string>
#include "News.h"

News::News(std::string id, std::string content, std::string title, std::string category) : Data(id, content) {
  this->title = title;
  this->category = category;
}

std::string News::getTitle() {
  return title;
}

std::string News::getCategory() {
  return category;
}