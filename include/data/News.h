#ifndef NEWS_H
#define NEWS_H

#include <string>
#include "Data.h"
#include "Category.h"

class News : public Data {
public:
  News(std::string id, std::string content, std::string title, std::Category category);
  std::string getTitle();
  std::Category getCategory();
private:
  std::string title;
  std::Category category;
};

#endif