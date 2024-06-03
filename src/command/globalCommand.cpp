#include "command/GlobalCommand.h"
#include "command/UserCommand.h"
#include <iostream>
#include <string>
#include <cstdlib>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

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
  int choice = 0;
  std::cout << YELLOW << "===== Main Menu =====" << RESET << std::endl;
  std::cout << GREEN << "1. Sign Up" << RESET << std::endl;
  std::cout << GREEN << "2. Sign In" << RESET << std::endl;
  std::cout << RED << "3. Exit" << RESET << std::endl;
  std::cout << "Enter your choice: ";

  while (!(std::cin >> choice) || choice < 1 || choice > 3) {
    std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the input buffer
    std::cout << "Enter your choice: ";
  }

  UserCommand userCommand(userDb);

  #if defined(_WIN32) || defined(_WIN64)
  system("cls"); // Windows
  #else
  system("clear"); // UNIX/Linux/macOS
  #endif

  switch (choice) {
    case 1:
      userCommand.signUp();
      break;
    case 2:
      userCommand.signIn();
      break;
    case 3:
      std::cout << "Exiting the program. Good Bye." << std::endl;
      break;
    default:
      std::cout << "Unknown error occurred." << std::endl;
  }
}