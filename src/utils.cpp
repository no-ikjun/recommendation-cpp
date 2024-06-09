// #include "Category.h"
// #include "NewsDatabase.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// // 카테고리 문자열을 Category 열거형으로 변환하는 함수
// Category parseCategory(const std::string& categoryStr) {
//   if (categoryStr == "Entertainment") return Category::ENTERTAINMENT;
//   else if (categoryStr == "science") return Category::SCIENCE;
//   else if (categoryStr == "Health") return Category::HEALTH;
//   else if (categoryStr == "Politics") return Category::POLITICS;
//   else if (categoryStr == "Sports") return Category::SPORTS;
//   else if (categoryStr == "World") return Category::WORLD;
//   else if (categoryStr == "Tech") return Category::TECH;
//   else if (categoryStr == "Business") return Category::BUSINESS;
//   else return Category::NONE;
// }

// void loadNewsFromCSV(const std::string& filename, NewsDatabase* newsDb) {
//   std::ifstream file(filename);
//   std::string line;
  
//   std::getline(file, line);

//   std::cout << "Start loading news from " << filename << "\n";

//   int id = 1;
//   while (std::getline(file, line)) {
//     if (id  > 300) break;
//     std::istringstream ss(line);
//     std::string text, categoryStr, dummy;
    
//     std::getline(ss, dummy, '"');
//     std::getline(ss, text, '"');
//     std::getline(ss, dummy, ',');
//     std::getline(ss, categoryStr, ',');

//     // Category category = parseCategory(categoryStr);
//     // News* news = new News(std::to_string(id), "Generated Title", text, category);
//     // newsDb->add(news);
//     id++;
//   }
  
//   file.close();
// }

// void printPreferences(const std::vector<double>& preferences) {
//   std::cout << "Retrieved Preferences: ";
//   for (const double& value : preferences) {
//     std::cout << value << " ";
//   }
//   std::cout << std::endl;
// }