#ifndef NEWS_H
#define NEWS_H

#include <string>
#include "Data.h"
#include "Category.h"

class News : public Data {
public:
  News(std::string id, std::string content, std::string title, Category category);

  std::string getContent() override;
  
  void vectorEmbed() override;

  std::string getTitle() const;
  void setTitle(std::string);

  Category getCategory() const;
  void setCategory(Category);
  
private:
  std::string title;
  Category category;
};

#endif