#include "data/Category.h"

Category parseCategory(const std::string& categoryStr) {
  if (categoryStr == "Entertainment") return Category::ENTERTAINMENT;
  else if (categoryStr == "science") return Category::SCIENCE;
  else if (categoryStr == "Health") return Category::HEALTH;
  else if (categoryStr == "Politics") return Category::POLITICS;
  else if (categoryStr == "Sports") return Category::SPORTS;
  else if (categoryStr == "World") return Category::WORLD;
  else if (categoryStr == "Tech") return Category::TECH;
  else if (categoryStr == "Business") return Category::BUSINESS;
  else return Category::NONE;
}