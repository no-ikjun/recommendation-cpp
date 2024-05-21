#include <iostream>
#include "News.h"
#include "../category/Category.h"

News::News(
  const std::string& id,
  const std::string& title, 
  const std::string& content, 
  const Category& category
) : id(id), title(title), content(content), category(category) {}


