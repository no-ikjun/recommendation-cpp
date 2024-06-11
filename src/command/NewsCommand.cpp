#include "command/GlobalCommand.h"
#include "command/NewsCommand.h"
#include "session/UserSession.h"
#include "data/User.h"
#include "db/UserDatabase.h"
#include "recommender/Recommender.h"
#include "recommender/Word2Vec.h"
#include "recommender/Vocabulary.h"
#include "LinearAlgebra/ColumnVector.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void printWrappedText(const std::string& text, int maxWidth) {
  std::istringstream words(text);
  std::string word;
  int currentWidth = 0;

  while (words >> word) {
    if (currentWidth + word.length() > maxWidth) {
      std::cout << std::endl;
      currentWidth = 0;
    }
    if (currentWidth > 0) {
      std::cout << " ";
      currentWidth += 1;
    }
    std::cout << word;
    currentWidth += word.length();
  }
  std::cout << std::endl;
}

std::string promptInput(const std::string& prompt) {
  std::string input;
  std::cout << prompt << ": ";
  std::getline(std::cin, input);
  return input;
}


bool NewsCommand::printNews(std::string id) {
  try {
    News news = newsDb->get(id);
    std::string selectedOption;

    // Display news
    int width = 80;
    std::string title = news.getTitle();
    int padding = (width - title.length()) / 2;
    std::cout << std::string(padding, ' ') << GREEN << title << RESET << std::endl;
    std::cout << CYAN;
    printWrappedText(news.getContent(), width);
    std::cout << RESET << std::endl;
    selectedOption = promptInput("Next(n) | Quit(q)");
    if (selectedOption == "q" || selectedOption == "Q") {
      return false;
    } else if(selectedOption == "n" || selectedOption == "N") {
      return true;
    }
  } catch (const std::exception& e) {
    printError(e.what());
    return false;  // 예외 발생 시 함수 종료
  }
}

void NewsCommand::printError(const std::string& message) {
  std::cout << RED << "News Command Error: " << message << RESET << std::endl;
}