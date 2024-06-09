#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

enum class Category {
  ENTERTAINMENT, 
  SCIENCE,
  HEALTH,
  POLITICS,
  SPORTS,
  WORLD,
  TECH,
  BUSINESS,
  NONE
};

Category parseCategory(const std::string& categoryStr);

#endif