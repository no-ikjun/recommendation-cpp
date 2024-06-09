#include "data/News.h"
#include "LinearAlgebra/ColumnVector.h"
#include <iostream>

News::News() : id(""), title(""), content(""), category(Category::NONE), embedding(LinearAlgebra::ColumnVector(1)) {}

News::News(const std::string& id, const std::string& title,
           const std::string& content, Category category)
: id(id), title(title), content(content), category(category) , embedding(LinearAlgebra::ColumnVector(1)) {}

std::string News::getId() const {
  return id;
}

std::string News::getTitle() const {
  return title;
}

std::string News::getContent() const {
  return content;
}

Category News::getCategory() const {
  return category;
}

LinearAlgebra::ColumnVector News::getEmbedding() const {
  return embedding;
}

void News::setEmbedding(const LinearAlgebra::ColumnVector& embedding) {
  this->embedding = embedding;
}

void News::serialize(std::ostream& os) const {
  os.write(id.c_str(), id.size() + 1);
  os.write(title.c_str(), title.size() + 1);
  os.write(content.c_str(), content.size() + 1);
  auto categoryValue = static_cast<int>(category);
  os.write(reinterpret_cast<const char*>(&categoryValue), sizeof(categoryValue));
  embedding.serialize(os);
}

bool News::deserialize(std::istream& is) {
  std::getline(is, id, '\0');
  std::getline(is, title, '\0');
  std::getline(is, content, '\0');
  int categoryValue;
  is.read(reinterpret_cast<char*>(&categoryValue), sizeof(categoryValue));
  category = static_cast<Category>(categoryValue);
  embedding.deserialize(is);
  return !is.fail();
}
