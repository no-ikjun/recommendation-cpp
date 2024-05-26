#include "data/News.h"
#include "data/Category.h"
#include <iostream>

// Initialize the base class Data with the required parameters
News::News() : Data("", "", std::vector<double>()), title(""), category(Category::IT) {}

News::News(const std::string& id, const std::string& title, const std::string& content, Category category, const std::vector<double>& featureVector)
: Data(id, content, featureVector), title(title), category(category) {}

std::string News::getTitle() const {
  return title;
}

Category News::getCategory() const {
  return category;
}

void News::serialize(std::ostream& os) const {
  Data::serialize(os);  // 먼저 Data의 serialize를 호출
  os.write(title.c_str(), title.size() + 1);
  auto categoryValue = static_cast<int>(category);
  os.write(reinterpret_cast<const char*>(&categoryValue), sizeof(categoryValue));
}

bool News::deserialize(std::istream& is) {
  if (!Data::deserialize(is)) return false;
  std::getline(is, title, '\0');
  int categoryValue;
  is.read(reinterpret_cast<char*>(&categoryValue), sizeof(categoryValue));
  category = static_cast<Category>(categoryValue);
  return !is.fail();
}