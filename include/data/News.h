#ifndef NEWS_H
#define NEWS_H

#include <string>
#include "Data.h"
#include "Category.h"

class News : public Data {
public:
  News(std::string id, std::string content, std::string title, Category category);
  void vectorEmbed();
  std::string getTitle();
  Category getCategory();
private:
  std::string title;
  Category category;
};

#endif