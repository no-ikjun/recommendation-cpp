#ifndef NEWS_H
#define NEWS_H

#include <string>
#include "Category.h"

class News {
public:
  News();  // Default constructor
  News(const std::string& id, const std::string& title,
       const std::string& content, Category category);

  std::string getId() const;
  std::string getTitle() const;
  std::string getContent() const;
  Category getCategory() const;

  void serialize(std::ostream& os) const;
  bool deserialize(std::istream& is);

private:
  std::string id;
  std::string title;
  std::string content;
  Category category;
};

#endif // NEWS_H
