#include "command/GlobalCommand.h"
#include "command/NewsCommand.h"
#include <iostream>
#include <string>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
const std::string RESET = "\033[0m";

bool NewsCommand::printNews(std::string id) {
  try {
    News news = newsDb->get(id);
    std::cout << "Title: " << news.getTitle() << std::endl;
    std::cout << "Author: " << news.getAuthor() << std::endl;
    std::cout << "Content: " << news.getContent() << std::endl;
    return true;
  } catch (const std::exception& e) {
    printError(e.what());
    return false;
  }
}

void NewsCommand::printError(const std::string& message) {
  std::cout << RED << "News Command Error: " << message << RESET << std::endl;
}