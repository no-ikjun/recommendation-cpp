#ifndef NEWS_H
#define NEWS_H

#include <string>
#include "../category/Category.h"

class News {
public:
  News(const std::string& id, const std::string& title, const std::string& content, const Category& category) {}

  std::string getId() const {}
  
  std::string getTitle() const {}

  std::string getContent() const {}

  Category getCategory() const {}

private:
  std::string id;
  std::string title;
  std::string content;
  Category category;
};

#endif