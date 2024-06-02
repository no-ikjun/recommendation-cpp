#include "command/GlobalCommand.h"
#include <iostream>
#include <string>

bool GlobalCommand::continuePrompt() {
  std::string response;
  while (true) {
    std::cout << "Do you want to try again? (y/n): ";
    std::getline(std::cin, response);
    if (response == "y" || response == "Y") {
        return true;
    } else if (response == "n" || response == "N") {
        return false;
    } else {
        std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
    }
  }
}

void GlobalCommand::showMenu() {
  std::cout << "1. Sign Up" << std::endl;
  std::cout << "2. Sign In" << std::endl;
  std::cout << "3. Exit" << std::endl;
}