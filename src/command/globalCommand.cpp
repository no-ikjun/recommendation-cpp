#include "command/GlobalCommand.h"
#include "command/UserCommand.h"
#include <iostream>
#include <string>
#include <cstdlib>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
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
  std::cout << YELLOW << "\n===== Welcome to the News Recommendation System =====\n" << RESET;
  std::cout << GREEN << "1. Sign Up - Register as a new user" << RESET << std::endl;
  std::cout << GREEN << "2. Sign In - Access your account" << RESET << std::endl;
  std::cout << RED << "3. Exit - Close the application" << RESET << std::endl;
  std::cout << CYAN << "Enter your choice (1-3): " << RESET;
  
  while (!(std::cin >> choice) || choice < 1 || choice > 3) {
      std::cout << RED << "Invalid input. Please enter a number between 1 and 3: " << RESET;
      std::cin.clear(); // Clears error flag on cin
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discards the buffer
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

void GlobalCommand::printWelcome() {
  std::cout << YELLOW << R"(
     ___   ___  ____    ____            _           _   
    / _ \ / _ \|  _ \  |  _ \ _ __ ___ (_) ___  ___| |_ 
   | | | | | | | |_) | | |_) | '__/ _ \| |/ _ \/ __| __|
   | |_| | |_| |  __/  |  __/| | | (_) | |  __/ (__| |_ 
    \___/ \___/|_|     |_|   |_|  \___// |\___|\___|\__|
                                      |__/                                                
    )" << RESET << std::endl;
    std::cout << GREEN << "Welcome to the News Recommendation System!" << std::endl;
    std::cout << CYAN << "Discover news tailored just for you." << RESET << std::endl;
}

void GlobalCommand::printGoodbye() {
  std::cout << "Thank you for using News Today. Goodbye!" << std::endl;
}

void GlobalCommand::printError(const std::string& message) {
  std::cerr << "Error: " << message << std::endl;
}