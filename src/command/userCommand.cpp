#include "command/UserCommand.h"
#include "session/UserSession.h"
#include <iostream>
#include <sstream>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void UserCommand::signUp() {
  bool registrationSuccessful = false;
  do {
    std::string id, name, password;
    std::cout << "Sign Up " << YELLOW << "(Input Your Personal Information)" << RESET << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "ID: ";
    std::getline(std::cin, id);
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    try {
      User newUser(id, name, password, {});
      userDb->add(&newUser);
      std::cout << GREEN << "Registration successful." << RESET << std::endl;
      registrationSuccessful = true;
    } catch (const std::exception& e) {
      printError(e.what());
      std::cout << "Would you like to try registering again? (y/n): ";
      char response;
      std::cin >> response;
      if (response != 'y' && response != 'Y') {
        registrationSuccessful = true; // End loop if user does not want to retry
      }
    }
  } while (!registrationSuccessful);
}

void UserCommand::signIn() {
  bool loginSuccessful = false;
  do {
    std::string id, password;
    std::cout << "Sign In" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "ID: ";
    std::getline(std::cin, id);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    try {
      User user = userDb->get(id);
      if (user.getPassword() == password) {
        UserSession* session = UserSession::getInstance();
        session->login(user.getId(), user.getName());
        std::cout << GREEN << "Login successful. Welcome, " << session->getUserName() << "!" << RESET << std::endl;
        loginSuccessful = true;
      } else {
        std::cout << RED << "Invalid password. Please try again." << RESET << std::endl;
      }
    } catch (const std::exception& e) {
        std::cout << RED << "Login failed: " << e.what() << RESET << std::endl;
        std::cout << "Would you like to try logging in again? (y/n): ";
        char response;
        std::cin >> response;
        if (response != 'y' && response != 'Y') {
        loginSuccessful = true;
      }
    }
  } while (!loginSuccessful);
}

void UserCommand::setPref() {
  std::cout << "Setting preferences...\n";
  std::cout << "Enter your interests separated by spaces (e.g., technology science business): ";

  std::string input;
  std::getline(std::cin, input);  // 전체 라인 입력 받기

  std::istringstream iss(input);
  std::vector<std::string> interests;
  std::string interest;

  // 공백을 기준으로 입력 받은 라인을 나누기
  while (iss >> interest) {
      interests.push_back(interest);
  }

  // 저장된 관심사 출력
  std::cout << "You have entered the following interests:\n";
  for (const auto& item : interests) {
      std::cout << "- " << item << std::endl;
  }
}

void UserCommand::printError(const std::string& message) {
  std::cout << RED << "User Command Error: " << message << RESET << std::endl;
}